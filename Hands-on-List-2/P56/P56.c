/*
 * P56 / P56.c
 * Revision notes:
 *   - This program belongs to the OS lab collection and is designed for
 *     revision, tracing, and debugging of a single Linux programming concept.
 *   - Program entry point for a focused operating-system exercise.
 *   - The code is intentionally kept compact and readable so the core
 *     system call flow, error handling, and resource cleanup are easy to
 *     follow during study or review.
 *   - Read the matching exercise description and README.md before changing
 *     behavior; the goal here is to preserve the teaching example while
 *     making it easier to revisit.
 *
 * Review checklist:
 *   - Confirm the call sequence and every return path.
 *   - Check all cleanup operations such as close(), unlink(), wait(), and
 *     IPC teardown before exiting.
 *   - Verify the signal, pipe, socket, or synchronization behavior against
 *     the expected operating-system model.
 */

#define _GNU_SOURCE
#include <inttypes.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#if defined(__i386__) || defined(__x86_64__)
static inline uint64_t tsc_start(void) {
    unsigned lo, hi;
    __asm__ volatile("lfence; rdtsc" : "=a"(lo), "=d"(hi)::"memory");
    return ((uint64_t)hi << 32) | lo;
}

static inline uint64_t tsc_end(void) {
    unsigned lo, hi, aux;
    __asm__ volatile("rdtscp; lfence"
                     : "=a"(lo), "=d"(hi), "=c"(aux)::"memory");
    return ((uint64_t)hi << 32) | lo;
}

#else
#error "This exercise requires an x86/x86-64 Linux CPU with RDTSC/RDTSCP."
#endif
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    volatile long result = 0;
    uint64_t a = tsc_start();
    for (int i = 0; i < 100; i++)
        result = syscall(SYS_getppid);
    uint64_t b = tsc_end();
    printf("100 getppid() syscalls returned last value %ld\n", result);
    printf("Elapsed timestamp-counter ticks: %" PRIu64 "\n", b - a);
    return 0;
}
