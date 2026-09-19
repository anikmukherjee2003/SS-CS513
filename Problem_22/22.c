/*
 * Problem 21: Writing to a file from parent and child
 *
 * Problem statement: Open a file, call fork(), allow both parent and child processes to write to it, and examine the resulting file.
 */

/* Opens a truncated output file before fork(), so parent and child share its open
 * descriptor.  The child writes first; wait() makes the parent write its message
 * afterward, producing deterministic file order.
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t pid;
    int fd;
    fd = open("22.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    pid = fork();

    if (pid == -1) {
        perror("Error creating child process");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        //executed by the child process
        const char *child_message = "File written by child process.\n";
        write(fd, child_message, strlen(child_message));
        printf("Child wrote in the file.\n");
        close(fd);
    } 
    else {
        //executed by the parent process
        wait(NULL); //parent wait for the child proc to finish ::: ensuring child write first
        const char *parent_message = "File written by parent process.\n";
        write(fd, parent_message, strlen(parent_message));
        printf("Parent wrote in the file.\n");
        close(fd);
    }
    close(fd);
    return 0;
}



