/*
 * P55 / P55.c
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

static void print_limit(const char *label, struct rlimit x) {
    printf("%s soft=", label);
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
    struct rlimit x;
    if (getrlimit(RLIMIT_FSIZE, &x) == -1) {
        perror("getrlimit");
        return 1;
    }
    print_limit("RLIMIT_FSIZE before", x);
    rlim_t target = 1024;
    if (x.rlim_cur != RLIM_INFINITY && x.rlim_cur < target)
        target = x.rlim_cur;
    if (x.rlim_max != RLIM_INFINITY && x.rlim_max < target)
        target = x.rlim_max;
    x.rlim_cur = target;
    if (setrlimit(RLIMIT_FSIZE, &x) == -1) {
        perror("setrlimit");
        return 1;
    }
    if (getrlimit(RLIMIT_FSIZE, &x) == -1) {
        perror("getrlimit after");
        return 1;
    }
    print_limit("RLIMIT_FSIZE after", x);
    return 0;
}
