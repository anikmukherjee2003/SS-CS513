/*
 * Problem 23: Creating an orphan process
 *
 * Problem statement: Create an orphan process by allowing the parent to exit before the child, then observe the child's reparenting.
 */

/* After fork(), the parent sleeps five seconds and exits with _exit(), while the
 * child sleeps ten seconds and continues.  The differing lifetimes demonstrate
 * parent/child scheduling and reparenting behavior.
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        printf("Parent sleeping for 5 seconds...\n");
        fflush(stdout);

        sleep(5);

        printf("Parent exiting now\n");
        fflush(stdout);
        _exit(0);
    } else {
        printf("Child PID: %d\n", getpid());
        printf("Original PPID: %d\n", getppid());
        printf("Child sleeping for 10 seconds...\n");
        fflush(stdout);

        sleep(10);

        printf("Child awake\n");
        printf("New PPID: %d\n", getppid());
        fflush(stdout);
    }

    return 0;
}



