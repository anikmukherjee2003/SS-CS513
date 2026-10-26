/*
 * P32 / P32.c
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
    int fd[2];
    pid_t child;
    const char msg[] = "Data sent by the parent process";
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
    child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        char b[128];
        ssize_t n;
        close(fd[1]);
        n = read(fd[0], b, sizeof b - 1);
        if (n == -1) {
            perror("child read");
            _exit(1);
        }
        b[n] = '\0';
        printf("Child received: %s\n", b);
        fflush(stdout);
        close(fd[0]);
        _exit(0);
    }
    close(fd[0]);
    if (write(fd[1], msg, sizeof msg) == -1)
        perror("parent write");
    close(fd[1]);
    if (waitpid(child, NULL, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    return 0;
}
