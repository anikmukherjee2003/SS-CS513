/*
 * P57 / common.h
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

#ifndef OSLAB_P57_COMMON_H
#define OSLAB_P57_COMMON_H
#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static int print_limit(const char *label, int name) {
    errno = 0;
    long v = sysconf(name);
    if (v == -1) {
        if (errno)
            perror("sysconf");
        else
            printf("%s: indeterminate\n", label);
        return errno ? 1 : 0;
    }
    printf("%s: %ld\n", label, v);
    return 0;
}

#endif
