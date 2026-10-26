/*
 * Problem 29: Getting and modifying scheduling policy
 *
 * Problem statement: Obtain the current scheduling policy and attempt to modify it using policies such as SCHED_FIFO and SCHED_RR.
 */

/* Reads the current scheduler policy, attempts to switch the process to SCHED_FIFO,
 * then to SCHED_RR, using sched_param.sched_priority for each request.  The helper
 * translates returned policy constants into readable names.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

void print_policy(int policy) {
    switch (policy) {
        case SCHED_FIFO:
            printf("Current policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Current policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Current policy: SCHED_OTHER\n");
            break;
        default:
            printf("Current policy: Unknown\n");
            break;
    }
}

int main() {
    int policy;
    struct sched_param param;

    // Get current scheduling policy
    policy = sched_getscheduler(getpid());
    print_policy(policy);

    // Set the scheduling policy to SCHED_FIFO
    param.sched_priority = 10; 
    if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler SCHED_FIFO");
        exit(EXIT_FAILURE);
    }

    printf("Changed scheduling policy to SCHED_FIFO\n");

    policy = sched_getscheduler(getpid());
    print_policy(policy);

    // Set the scheduling policy back to SCHED_RR
    param.sched_priority = 10; 
    if (sched_setscheduler(getpid(), SCHED_RR, &param) == -1) {
        perror("sched_setscheduler SCHED_RR");
        exit(EXIT_FAILURE);
    }
    printf("Changed scheduling policy to SCHED_RR\n");
    policy = sched_getscheduler(getpid());
    print_policy(policy);
    return 0;
}



