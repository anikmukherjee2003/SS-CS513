/*
 * P52 / server_common.h
 * Revision notes:
 *   - This header belongs to the OS lab collection and is designed for
 *     revision, tracing, and debugging of a single Linux programming concept.
 *   - Shared declarations and utilities used by the exercise family.
 *   - The code is intentionally kept compact and readable so the core
 *     system call flow, error handling, and resource cleanup are easy to
 *     follow during study or review.
 *   - Read the matching exercise description and README.md before changing
 *     behavior; the goal here is to preserve the teaching example while
 *     making it easier to revisit.
 *
 * Review checklist:
 *   - Confirm the call sequence and every return path.
 *   - Check all cleanup operations such as close(), unlink(), wait(), and
 *     IPC teardown before exiting.
 *   - Verify the signal, pipe, socket, or synchronization behavior against
 *     the expected operating-system model.
 */

#ifndef OSLAB_P52_SERVER_COMMON_H
#define OSLAB_P52_SERVER_COMMON_H
#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static void serve_client(int fd) {
    char b[1024];
    ssize_t n = recv(fd, b, sizeof b - 1, 0);
    if (n > 0) {
        b[n] = '\0';
        printf("Client %ld: %s\n", (long)getpid(), b);
        send(fd, b, (size_t)n, 0);
    }
    close(fd);
}

static void *thread_entry(void *arg) {
    int fd = *(int *)arg;
    free(arg);
    serve_client(fd);
    return NULL;
}

static int run_server(int threaded, int argc, char **argv) {

    const char *port = argc > 1 ? argv[1] : "5052";
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        perror("socket");
        return 1;
    }

    int yes = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    struct sockaddr_in a = {.sin_family = AF_INET,
                            .sin_port = htons((unsigned short)atoi(port)),
                            .sin_addr.s_addr = htonl(INADDR_ANY)};

    if (bind(s, (struct sockaddr *)&a, sizeof a) == -1 || listen(s, 16) == -1) {
        perror("bind/listen");
        close(s);
        return 1;
    }

    printf("%s concurrent server listening on port %s\n", threaded ? "pthread" : "fork", port);

    if (!threaded)
        signal(SIGCHLD, SIG_IGN);

    for (;;) {
        int c = accept(s, NULL, NULL);
        if (c == -1) {
            if (errno == EINTR)
                continue;
            perror("accept");
            break;
        }

        if (threaded) {
            int *x = malloc(sizeof *x);
            if (!x) {
                perror("malloc");
                close(c);
                continue;
            }
            *x = c;
            pthread_t t;
            int e = pthread_create(&t, NULL, thread_entry, x);
            if (e) {
                fprintf(stderr, "pthread_create: %s\n", strerror(e));
                free(x);
                close(c);
            } else
                pthread_detach(t);
        }

        else {
            pid_t p = fork();
            if (p == 0) {
                close(s);
                serve_client(c);
                _exit(0);
            }
            if (p < 0)
                perror("fork");
            close(c);
        }
    }

    close(s);
    return 1;
}

#endif
