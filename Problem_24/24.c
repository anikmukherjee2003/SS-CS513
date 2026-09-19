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

int main(){

	if(fork()){
		printf("Parent process PID: %d\n", getpid());
        printf("Putting Parent process to sleep for 5...\n");
        sleep(5);
		printf("Parent is awake\n");
        printf("Exiting parent!\n");
		_exit(0);
	}else{
		printf("Child process PID: %d\n", getpid());
        printf("Putting Child process to sleep for 10s!\n");
        sleep(10);
        printf("Child is awake now\n");
	}
	return 0;
}



