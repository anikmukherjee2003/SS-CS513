/*
 * P47 / P47c.c
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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEYFILE "/tmp/oslab_sysv_shm_key"
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    key_t k = ftok(KEYFILE, 'S');
    if (k == (key_t)-1) {
        perror("ftok");
        return 1;
    }
    int id = shmget(k, 4096, 0);
    if (id == -1) {
        perror("shmget");
        return 1;
    }
    void *p = shmat(id, NULL, 0);
    if (p == (void *)-1) {
        perror("shmat");
        return 1;
    }
    printf("Attached to segment %d.\n", id);
    if (shmdt(p) == -1) {
        perror("shmdt");
        return 1;
    }
    puts("Detached from shared memory.");
    return 0;
}
