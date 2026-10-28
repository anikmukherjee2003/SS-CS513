/*
 * P38 / P38a.c
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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/* Server: run first; P38b sends one request and receives one reply. */
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    const char *r = "/tmp/oslab_p38_request", *s = "/tmp/oslab_p38_response";
    char b[256];
    ssize_t n;
    int in, out;
    if (mkfifo(r, 0600) == -1 && errno != EEXIST) {
        perror("mkfifo request");
        return EXIT_FAILURE;
    }
    if (mkfifo(s, 0600) == -1 && errno != EEXIST) {
        perror("mkfifo response");
        return EXIT_FAILURE;
    }
    in = open(r, O_RDONLY);
    if (in == -1) {
        perror("open request");
        return EXIT_FAILURE;
    }
    n = read(in, b, sizeof b - 1);
    close(in);
    if (n == -1) {
        perror("read");
        return EXIT_FAILURE;
    }
    b[n] = '\0';
    printf("Server received: %s\n", b);
    out = open(s, O_WRONLY);
    if (out == -1) {
        perror("open response");
        return EXIT_FAILURE;
    }
    if (write(out, "Reply from server", sizeof "Reply from server") == -1) {
        perror("write");
        close(out);
        return EXIT_FAILURE;
    }
    close(out);
    return EXIT_SUCCESS;
}
