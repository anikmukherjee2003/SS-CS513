/*
 * Process timing with the timestamp counter
 *
 * Problem statement: Measure and display the processor timestamp-counter interval around a getpid() system call.
 */

/* Measures the processor timestamp-counter interval around getpid().  rdtsc()
 * combines the 32-bit EDX:EAX values into uint64_t; the PID and tick difference
 * are then printed.
 */



#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static __inline__ uint64_t rdtsc(void) { //reading timestamp
    unsigned int low, high;
    __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t startTime, endTime;
    pid_t pid;

    startTime = rdtsc();  //time before
    pid = getpid();
    endTime = rdtsc();  //time after

    printf("PID: %d\n", pid);
    printf("Time taken by getpid(): %lu\n", (endTime - startTime));

    return 0;
}



