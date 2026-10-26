/*
 * P64 / P64a.c
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
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void continued(int s) {
    (void)s;
    const char m[] = "Resumed after SIGCONT; SIGSTOP was not caught.\n";
    write(STDOUT_FILENO, m, sizeof m - 1);
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    struct sigaction a = {0};
    a.sa_handler = continued;
    sigemptyset(&a.sa_mask);
    if (sigaction(SIGSTOP, &a, NULL) == -1)
        printf("sigaction(SIGSTOP) failed as expected: %s\n", strerror(errno));
    else
        puts("Unexpectedly installed a SIGSTOP handler.");
    signal(SIGCONT, continued);
    printf("Waiting process PID: %ld. Run P64b with this PID.\n", (long)getpid());
    fflush(stdout);
    for (;;)
        pause();
}
