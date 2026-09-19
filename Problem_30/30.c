/*
 * Problem 30: Running a task with a daemon process
 *
 * Problem statement: Create a daemon process that detaches from the terminal and runs a task at regular intervals.
 */

/* Forks a background child and exits the parent.  The child detaches with setsid(),
 * changes to /, clears its umask, then loops forever printing a heartbeat every four
 * seconds; this illustrates basic daemon setup and ongoing process behavior.
 */


#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    if(!fork()){
        setsid();
        chdir("/");
        umask(0);
            while(1){
                sleep(4);
                printf("Child PID: %d\n", getpid());
                printf("Daemon Process is running...\n");
            }
    }
    else    
        exit(0);
}

