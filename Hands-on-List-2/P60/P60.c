/*
 * P60 / P60.c
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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        perror("signal ignore");
        return 1;
    }
    puts("SIGINT ignored for 5 seconds. Press Ctrl-C now; it will be ignored.");
    fflush(stdout);
    sleep(5);
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
        perror("signal default");
        return 1;
    }
    puts("SIGINT reset to default. Press Ctrl-C to terminate.");
    fflush(stdout);
    for (;;)
        pause();
}
