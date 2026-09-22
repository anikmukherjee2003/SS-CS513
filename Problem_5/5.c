/*
 * Problem 5: Continuous file creation and descriptor inspection
 *
 * Create five files repeatedly in an infinite loop.
 * Run the program in the background and inspect
 * its open file descriptors using /proc/<pid>/fd.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[5];
    char filename[20];

    while (1) {
        // Open all five files
        for (int i = 0; i < 5; i++) {
            snprintf(filename, sizeof(filename),
                     "file%d.txt", i + 1);

            fd[i] = open(filename,
                         O_CREAT | O_WRONLY,
                         0644);

            if (fd[i] == -1) {
                perror("open");
                exit(1);
            }

            printf("Opened %s with FD = %d\n",
                   filename, fd[i]);
        }

        // Keep all descriptors open for inspection
        printf("All five files are open. PID = %d\n",
               getpid());
        fflush(stdout);

        sleep(30);

        // Close all five files
        for (int i = 0; i < 5; i++) {
            close(fd[i]);
        }

        printf("All files closed. Starting again...\n");
        sleep(2);
    }

    return 0;
}