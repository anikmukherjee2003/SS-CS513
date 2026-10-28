/*
 * P63 / P63.c
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
#include <sys/types.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    pid_t parent = getpid();
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        sleep(1);
        printf("Child %ld sends SIGKILL to parent %ld.\n", (long)getpid(),
               (long)parent);
        fflush(stdout);
        if (kill(parent, SIGKILL) == -1) {
            perror("kill");
            _exit(1);
        }
        sleep(2);
        printf("Child is now orphaned; new PPID=%ld.\n", (long)getppid());
        fflush(stdout);
        _exit(0);
    }
    printf("Parent %ld created child %ld and waits to be killed.\n",
           (long)parent, (long)child);
    fflush(stdout);
    for (;;)
        pause();
}
