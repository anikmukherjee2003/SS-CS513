/*
 * P31 / P31.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {

    int fd[2];

    const char message[] = "Hello through a pipe!";

    char buffer[128];

    ssize_t n;

    if (pipe(fd) == -1) {

        perror("pipe");

        return EXIT_FAILURE;
    }

    if (write(fd[1], message, sizeof message) == -1) {

        perror("write");

        close(fd[0]);

        close(fd[1]);

        return EXIT_FAILURE;
    }

    close(fd[1]);

    n = read(fd[0], buffer, sizeof buffer - 1);

    if (n == -1) {

        perror("read");

        close(fd[0]);

        return EXIT_FAILURE;
    }

    buffer[n] = '\0';

    printf("Read from pipe: %s\n", buffer);

    close(fd[0]);

    return EXIT_SUCCESS;
}
