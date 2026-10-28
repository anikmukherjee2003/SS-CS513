/*
 * P51 / P51a.c
 * Revision notes:
 *   - This program belongs to the OS lab collection and is designed for
 *     revision, tracing, and debugging of a single Linux programming concept.
 *   - Program entry point for a focused operating-system exercise.
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

#define _POSIX_C_SOURCE 200809L
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(int argc, char **argv) {
    const char *port = argc > 1 ? argv[1] : "5051";
    struct addrinfo h = {0}, *list, *p;
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_STREAM;
    h.ai_flags = AI_PASSIVE;
    int e = getaddrinfo(NULL, port, &h, &list);
    if (e) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
        return 1;
    }
    int s = -1;
    for (p = list; p; p = p->ai_next) {
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s == -1)
            continue;
        int yes = 1;
        setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
        if (bind(s, p->ai_addr, p->ai_addrlen) == 0 && listen(s, 8) == 0)
            break;
        close(s);
        s = -1;
    }
    freeaddrinfo(list);
    if (s == -1) {
        perror("bind/listen");
        return 1;
    }
    printf(
        "TCP server listening on port %s; start P51b on the other machine.\n",
        port);
    int c = accept(s, NULL, NULL);
    if (c == -1) {
        perror("accept");
        close(s);
        return 1;
    }
    char b[1024];
    ssize_t n = recv(c, b, sizeof b - 1, 0);
    if (n == -1) {
        perror("recv");
        close(c);
        close(s);
        return 1;
    }
    b[n] = '\0';
    printf("Client says: %s\n", b);
    if (send(c, b, (size_t)n, 0) == -1)
        perror("send");
    close(c);
    close(s);
    return 0;
}
