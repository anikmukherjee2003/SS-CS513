/*
 * Problem 2: Exploring a background process through /proc
 *
 * Problem statement: Create a program that runs indefinitely in the background, traverse /proc, and extract relevant information from process directories.
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    /* Infinite loop: the process keeps executing forever until manually stopped. */
    while (1) {
        /* getpid() returns the PID of this current process.
         * This is the identifier Linux uses to track it.
         */
        printf("Running process with PID: %d\n", getpid());

        /* sleep(5) pauses execution for 5 seconds so the output is visible and
         * the process remains alive long enough to inspect from another terminal.
         */
        sleep(5);
    }

    return 0;
}

