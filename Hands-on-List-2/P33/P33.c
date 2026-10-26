/*
 * P33 / P33.c
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
#include <sys/wait.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    int pc[2], cp[2];
    pid_t child;
    const char q[] = "Hello child";
    char reply[128];
    if (pipe(pc) == -1 || pipe(cp) == -1) {
        perror("pipe");
        return 1;
    }
    child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        char req[128];
        close(pc[1]);
        close(cp[0]);
        ssize_t n = read(pc[0], req, sizeof req - 1);
        if (n == -1) {
            perror("read");
            _exit(1);
        }
        req[n] = '\0';
        printf("Child received: %s\n", req);
        fflush(stdout);
        if (write(cp[1], "Hello parent", sizeof "Hello parent") == -1)
            perror("write");
        close(pc[0]);
        close(cp[1]);
        _exit(0);
    }
    close(pc[0]);
    close(cp[1]);
    if (write(pc[1], q, sizeof q) == -1)
        perror("parent write");
    close(pc[1]);
    ssize_t n = read(cp[0], reply, sizeof reply - 1);
    if (n == -1) {
        perror("parent read");
        close(cp[0]);
        return 1;
    }
    reply[n] = '\0';
    printf("Parent received: %s\n", reply);
    close(cp[0]);
    if (waitpid(child, NULL, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    return 0;
}
