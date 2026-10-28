/*
 * P40 / P40.c
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

#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    struct rlimit l;
    int p[2];
    if (getrlimit(RLIMIT_NOFILE, &l) == -1) {
        perror("getrlimit");
        return EXIT_FAILURE;
    }
    if (l.rlim_cur == RLIM_INFINITY)
        puts("Maximum open files (soft limit): unlimited");
    else
        printf("Maximum open files (soft limit): %llu\n",
               (unsigned long long)l.rlim_cur);
    if (pipe(p) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    int n = fcntl(p[0], F_GETPIPE_SZ);
    if (n == -1) {
        perror("fcntl(F_GETPIPE_SZ)");
        close(p[0]);
        close(p[1]);
        return EXIT_FAILURE;
    }
    printf("Pipe capacity: %d bytes\n", n);
    close(p[0]);
    close(p[1]);
    return EXIT_SUCCESS;
}
