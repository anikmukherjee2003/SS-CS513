/*
 * P64 / P64b.c
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
#include <stdlib.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PID_OF_P64a\n", argv[0]);
        return 2;
    }
    char *end;
    long p = strtol(argv[1], &end, 10);
    if (*end || p <= 0) {
        fprintf(stderr, "Invalid PID\n");
        return 2;
    }
    if (kill((pid_t)p, SIGSTOP) == -1) {
        perror("kill SIGSTOP");
        return 1;
    }
    printf("Sent SIGSTOP to %ld. Target is now stopped.\n", p);
    sleep(2);
    if (kill((pid_t)p, SIGCONT) == -1) {
        perror("kill SIGCONT");
        return 1;
    }
    puts("Sent SIGCONT; the target resumes and reports that SIGSTOP could not "
         "be caught.");
    return 0;
}
