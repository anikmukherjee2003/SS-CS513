/*
 * Problem 28: Determining and modifying process priority
 *
 * Problem statement: Determine the current process priority and modify it using the nice() system call.
 */

/* Converts the requested niceness adjustment from argv, reports the current nice
 * value, applies nice(), and prints the returned new value.
 */




#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if(argc < 2){
		perror("Enter a new Priority Number for your application: \n");
		return 1;
	}

	int newPriority = atoi(argv[1]);
	int priority = nice(0);

	printf("The Current Priority was %d\n", priority);
	priority = nice(newPriority);
	printf("The New Priority is %d\n", priority);

	return 0;
}



