/*
 * Problem 20: Printing parent and child process IDs
 *
 * Problem statement: Call fork() and print the process IDs of the parent and child processes.
 */

/* fork() splits execution into parent and child paths.  Each path prints its own
 * PID and the related PID returned by getpid(), getppid(), or fork().
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h> 

int main() {

    pid_t pid;
    pid = fork();
    if (pid == 0)
        printf("Child process: PID = %d, Parent process: PID = %d\n", getpid(), getppid()); //exec by child process
    else 
        printf("Parent process: PID = %d, Child process: PID = %d\n", getpid(), pid); //exec by parent process
    return 0;
}


