/*
 * P59 / catch_signal_common.h
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

#ifndef OSLAB_P59_CATCH_SIGNAL_COMMON_H
#define OSLAB_P59_CATCH_SIGNAL_COMMON_H
#define _DEFAULT_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

static volatile sig_atomic_t caught_signal = 0;

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static void signal_handler(int sig) {
    caught_signal = sig;
    const char *m = "Caught signal.\n";
    switch (sig) {
    case SIGSEGV:
        m = "Caught SIGSEGV using signal().\n";
        break;
    case SIGINT:
        m = "Caught SIGINT using signal().\n";
        break;
    case SIGFPE:
        m = "Caught SIGFPE using signal().\n";
        break;
    case SIGALRM:
        m = "Caught SIGALRM using signal().\n";
        break;
    case SIGVTALRM:
        m = "Caught SIGVTALRM using signal().\n";
        break;
    case SIGPROF:
        m = "Caught SIGPROF using signal().\n";
        break;
    }
    write(STDOUT_FILENO, m, __builtin_strlen(m));
    if (sig == SIGSEGV)
        _exit(0);
}

static int run_signal(int sig, int timer_kind, int trigger_fault) {

    if (signal(sig, signal_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    if (trigger_fault) {
        volatile int *p = (volatile int *)0;
        *p = 1;
        return 1;
    }

    if (sig == SIGFPE) {
        raise(SIGFPE);
        return 0;
    }

    if (timer_kind == -2) {
        puts("Waiting for SIGINT; press Ctrl-C.");
        fflush(stdout);
        while (!caught_signal)
            pause();
        return 0;
    }

    if (timer_kind == -1) {
        puts("alarm(2) armed.");
        fflush(stdout);
        alarm(2);
        while (!caught_signal)
            pause();
        return 0;
    }

    if (timer_kind >= 0) {
        struct itimerval t = {0};
        t.it_value.tv_sec = 2;
        if (setitimer(timer_kind, &t, NULL) == -1) {
            perror("setitimer");
            return 1;
        }
        printf("setitimer armed for signal %d.\n", sig);
        fflush(stdout);
        if (timer_kind == ITIMER_REAL) {
            while (!caught_signal)
                pause();
        } else {
            while (!caught_signal)
                __asm__ volatile("" ::: "memory");
        }
        struct itimerval off = {0};
        setitimer(timer_kind, &off, NULL);
        return 0;
    }

    return 0;
}

#endif
