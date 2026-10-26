/*
 * P53 / timer_common.h
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

#ifndef OSLAB_P53_TIMER_COMMON_H
#define OSLAB_P53_TIMER_COMMON_H
#define _DEFAULT_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

static volatile sig_atomic_t timer_fired = 0;

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static void timer_handler(int sig) {
    (void)sig;
    timer_fired = 1;
}

static int run_timer(int which, int sig, const char *label) {

    struct sigaction sa = {0};
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    struct itimerval t = {.it_value = {.tv_sec = 10, .tv_usec = 0},
                          .it_interval = {.tv_sec = 0, .tv_usec = 10}};

    if (setitimer(which, &t, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("%s: first expiry is 10 seconds; repeat interval is 10 microseconds.\n", label);
    fflush(stdout);

    if (which == ITIMER_REAL) {
        while (!timer_fired)
            pause();
    }

    else {
        while (!timer_fired)
            __asm__ volatile("" ::: "memory");
    }

    struct itimerval stop = {0};
    if (setitimer(which, &stop, NULL) == -1) {
        perror("disarm timer");
        return 1;
    }

    puts("Timer expired; repeating interval was disarmed.");
    return 0;
}

#endif
