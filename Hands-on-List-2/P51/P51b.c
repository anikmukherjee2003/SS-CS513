/*
 * P51 / P51b.c
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s SERVER_HOST [PORT] [MESSAGE]\n", argv[0]);
        return 2;
    }
    const char *port = argc > 2 ? argv[2] : "5051";
    const char *msg = argc > 3 ? argv[3] : "Hello from the client machine";
    struct addrinfo h = {0}, *list, *p;
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_STREAM;
    int e = getaddrinfo(argv[1], port, &h, &list);
    if (e) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
        return 1;
    }
    int s = -1;
    for (p = list; p; p = p->ai_next) {
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s != -1 && connect(s, p->ai_addr, p->ai_addrlen) == 0)
            break;
        if (s != -1)
            close(s);
        s = -1;
    }
    freeaddrinfo(list);
    if (s == -1) {
        perror("connect");
        return 1;
    }
    if (send(s, msg, strlen(msg), 0) == -1) {
        perror("send");
        close(s);
        return 1;
    }
    char b[1024];
    ssize_t n = recv(s, b, sizeof b - 1, 0);
    if (n == -1) {
        perror("recv");
        close(s);
        return 1;
    }
    b[n] = '\0';
    printf("Server echoed: %s\n", b);
    close(s);
    return 0;
}
