/*
 * P48 / P48b.c
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    int id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if (id == -1) {
        perror("semget");
        return 1;
    }
    union semun arg;
    arg.val = 5;
    if (semctl(id, 0, SETVAL, arg) == -1) {
        perror("SETVAL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }
    printf("Counting semaphore ID: %d; initial value: 5\nRemove it with: ipcrm "
           "-s %d\n",
           id, id);
    return 0;
}
