/*
 * P37 / P37a.c
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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Reader. Start P37b first; it creates the FIFO and blocks until this reader
 * opens it. */
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(int argc, char **argv) {
    const char *p = argc > 1 ? argv[1] : "/tmp/oslab_p37_fifo";
    int fd = open(p, O_RDONLY);
    char b[256];
    ssize_t n;
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    n = read(fd, b, sizeof b - 1);
    if (n == -1) {
        perror("read");
        close(fd);
        return EXIT_FAILURE;
    }
    b[n] = '\0';
    printf("Reader received: %s\n", b);
    close(fd);
    return EXIT_SUCCESS;
}
