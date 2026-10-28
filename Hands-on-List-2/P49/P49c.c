/*
 * P49 / P49c.c
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
#include <sys/wait.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

static int op(int id, short n) {
    struct sembuf b = {.sem_num = 0, .sem_op = n, .sem_flg = 0};
    return semop(id, &b, 1);
}

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
    union semun u;
    u.val = 2;
    if (semctl(id, 0, SETVAL, u) == -1) {
        perror("SETVAL");
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        pid_t p = fork();
        if (p == -1) {
            perror("fork");
            break;
        }
        if (p == 0) {
            if (op(id, -1) == -1)
                _exit(1);
            printf("PID %ld acquired one of two pseudo-resources\n",
                   (long)getpid());
            fflush(stdout);
            sleep(1);
            if (op(id, 1) == -1)
                _exit(1);
            _exit(0);
        }
    }
    while (wait(NULL) > 0) {
    }
    semctl(id, 0, IPC_RMID);
    puts("Counting semaphore removed.");
    return 0;
}
