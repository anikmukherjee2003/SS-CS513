/*
 * Problem 22: Creating a zombie process
 *
 * Problem statement: Create a child process that terminates while its parent delays reaping it, producing a zombie process.
 */

/* Creates a child with fork().  The child sleeps five seconds and exits with
 * _exit(); the parent sleeps ten seconds, then wait() reaps the child.
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){

	if(fork()){
		printf("Parent process PID: %d\n", getpid());

		printf("Putting the parent to sleep for 10...\n");
        sleep(10);
        printf("Parent is awake now\n");

		wait(NULL);
	}else{
		printf("Child process PID: %d\n", getpid());

		printf("Putting the child to sleep for 5...\n");
        sleep(5);
        printf("Child is awake now\n");

		printf("Child exited\n");
		_exit(0);
	}
	return 0;
}


