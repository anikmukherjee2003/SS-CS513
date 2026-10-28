/*
 * P47 / P47a.c
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
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define KEYFILE "/tmp/oslab_sysv_shm_key"
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    int f = open(KEYFILE, O_CREAT | O_RDWR, 0600);
    if (f == -1) {
        perror("open key file");
        return 1;
    }
    close(f);
    key_t k = ftok(KEYFILE, 'S');
    if (k == (key_t)-1) {
        perror("ftok");
        return 1;
    }
    int id = shmget(k, 4096, IPC_CREAT | 0660);
    if (id == -1) {
        perror("shmget");
        return 1;
    }
    char *p = shmat(id, NULL, 0);
    if (p == (void *)-1) {
        perror("shmat");
        return 1;
    }
    snprintf(p, 4096, "Shared-memory text written by P47a (PID %ld)",
             (long)getpid());
    printf("Wrote: %s\nShared memory ID: %d\n", p, id);
    if (shmdt(p) == -1) {
        perror("shmdt");
        return 1;
    }
    puts("Segment remains available for P47b/P47c/P47d.");
    return 0;
}
