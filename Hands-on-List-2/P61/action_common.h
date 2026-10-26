/*
 * P61 / action_common.h
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

#ifndef OSLAB_P61_ACTION_COMMON_H
#define OSLAB_P61_ACTION_COMMON_H
#define _DEFAULT_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t got_signal = 0;

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static void action_handler(int s) {
    got_signal = s;
    const char *m = "Caught signal with sigaction().\n";
    if (s == SIGSEGV)
        m = "Caught SIGSEGV using sigaction().\n";
    else if (s == SIGINT)
        m = "Caught SIGINT using sigaction().\n";
    else if (s == SIGFPE)
        m = "Caught SIGFPE using sigaction().\n";
    write(STDOUT_FILENO, m, __builtin_strlen(m));
    if (s == SIGSEGV)
        _exit(0);
}

static int run_action(int sig) {
    struct sigaction a = {0};
    a.sa_handler = action_handler;
    sigemptyset(&a.sa_mask);
    if (sigaction(sig, &a, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    if (sig == SIGSEGV) {
        volatile int *p = (volatile int *)0;
        *p = 1;
    } else if (sig == SIGFPE)
        raise(SIGFPE);
    else {
        puts("Waiting for SIGINT; press Ctrl-C.");
        fflush(stdout);
        while (!got_signal)
            pause();
    }
    return 0;
}

#endif
