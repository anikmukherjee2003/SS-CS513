/*
 * P58 / P58.c
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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

static void *worker(void *arg) {
    long n = (long)arg;
    printf("Worker %ld: pthread_self=%lu, Linux TID=%ld\n", n, (unsigned long)pthread_self(),
           (long)syscall(SYS_gettid));
    return NULL;
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    pthread_t t[3];
    for (long i = 0; i < 3; i++) {
        int e = pthread_create(&t[i], NULL, worker, (void *)i);
        if (e) {
            fprintf(stderr, "pthread_create: %s\n", strerror(e));
            return 1;
        }
        printf("Created thread %ld: pthread_t=%lu\n", i, (unsigned long)t[i]);
    }
    for (int i = 0; i < 3; i++) {
        int e = pthread_join(t[i], NULL);
        if (e) {
            fprintf(stderr, "pthread_join: %s\n", strerror(e));
            return 1;
        }
    }
    return 0;
}
