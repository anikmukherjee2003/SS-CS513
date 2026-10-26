/*
 * P54 / P54.c
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
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

static void show(const char *n, int r) {
    struct rlimit x;
    if (getrlimit(r, &x) == -1) {
        perror(n);
        return;
    }
    printf("%-18s soft=", n);
    if (x.rlim_cur == RLIM_INFINITY)
        printf("unlimited");
    else
        printf("%llu", (unsigned long long)x.rlim_cur);
    printf(" hard=");
    if (x.rlim_max == RLIM_INFINITY)
        puts("unlimited");
    else
        printf("%llu\n", (unsigned long long)x.rlim_max);
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    show("CPU", RLIMIT_CPU);
    show("FSIZE", RLIMIT_FSIZE);
    show("DATA", RLIMIT_DATA);
    show("STACK", RLIMIT_STACK);
    show("CORE", RLIMIT_CORE);
    show("NOFILE", RLIMIT_NOFILE);
    show("AS", RLIMIT_AS);
    show("NPROC", RLIMIT_NPROC);
    show("MEMLOCK", RLIMIT_MEMLOCK);
    return 0;
}
