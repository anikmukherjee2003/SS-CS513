/*
 * Problem 27: Getting real-time priority limits
 *
 * Problem statement: Retrieve and display the maximum and minimum real-time priorities supported by the scheduling policy.
 */

/* Queries the highest and lowest priorities supported by the SCHED_RR policy with
 * sched_get_priority_max/min(), reporting errors if either scheduler call fails.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(){
	int maxPriority,minPriority;
	if((maxPriority = sched_get_priority_max(SCHED_RR)) == -1){
		perror("Error while getting Max Priority\n");
		return 0;
	}
	printf("Max Priority: %d\n",maxPriority);

	if((minPriority = sched_get_priority_min(SCHED_RR)) == -1){
		perror("Error while getting Min Priority\n");
		return 0;
	}
	printf("Min Priority: %d\n",minPriority);
	return 0;
}


