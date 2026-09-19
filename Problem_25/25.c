/*
 * Problem 24: Creating and waiting for child processes
 *
 * Problem statement: Create three child processes and have the parent wait for a specific child using waitpid().
 */

/* Creates children A, B, and C with staggered sleep durations.  The parent uses
 * waitpid() specifically for C and examines status with WIFEXITED/WEXITSTATUS.
 */



#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){

	pid_t childA,childB,childC;
	pid_t childTerminated;
	int status;

	if((childA = fork()) == -1){
		perror("Error while creating child A\n");
		return 0;
	}
	if(childA == 0){
		printf("Child A created !!!\n");
		printf("Putting Child A to sleep for 5 secs\n");
		sleep(5);
		printf("Child A Woke up\n");
		_exit(0);
	}

	if((childB = fork()) == -1){
		perror("Error while creating child B\n");
		return 0;
	}
	if(childB == 0){
		printf("Child B Created\n");
		printf("Putting Child B to sleep for 10 secs\n");
		sleep(10);
		printf("Child B Woke up\n");
		_exit(0);
	}

	if((childC = fork()) == -1){
		perror("Error while creating child C\n");
		return 0;
	}
	if(childC == 0){
		printf("Child C Created !!\n");
		printf("Putting Child C to sleep for 15 secs\n");
		sleep(15);
		printf("Child C Woke up\n");
		_exit(0);
	}

	printf("Parent waiting for Child C\n");
	childTerminated = waitpid(childC, &status, 0);
	
	if(childTerminated == childC){
		if (WIFEXITED(status)) {
			printf("Child C has exited with exit status: %d\n",
			       WEXITSTATUS(status));
		} else {
			printf("Child C did not exit normally\n");
		}
	}else{
		perror("waitpid");
	}
	return 0;
}
