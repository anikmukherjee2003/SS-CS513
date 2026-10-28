/*
 * P50 / P50.c
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

#include <errno.h>
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

static int change(int id, unsigned short n, short delta) {
    struct sembuf b = {.sem_num = n, .sem_op = delta, .sem_flg = 0};
    return semop(id, &b, 1);
}

static void child(int id, int first, int second, int ready[2], int gate[2]) {
    char c;
    if (change(id, (unsigned short)first, -1) == -1)
        _exit(2);
    close(ready[0]);
    close(gate[1]);
    if (write(ready[1], "R", 1) != 1)
        _exit(3);
    if (read(gate[0], &c, 1) != 1)
        _exit(4);
    fprintf(stderr, "Child %d holds semaphore %d and waits for %d.\n", first,
            first, second);
    if (change(id, (unsigned short)second, -1) == -1) {
        perror("semop after deadlock cleanup");
        _exit(0);
    }
    _exit(5);
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    int id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);
    if (id == -1) {
        perror("semget");
        return 1;
    }
    unsigned short vals[2] = {1, 1};
    union semun u;
    u.array = vals;
    if (semctl(id, 0, SETALL, u) == -1) {
        perror("SETALL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }
    int ready[2], gate[2];
    if (pipe(ready) == -1 || pipe(gate) == -1) {
        perror("pipe");
        semctl(id, 0, IPC_RMID);
        return 1;
    }
    pid_t a = fork();
    if (a == 0)
        child(id, 0, 1, ready, gate);
    if (a == -1) {
        perror("fork");
        return 1;
    }
    pid_t b = fork();
    if (b == 0)
        child(id, 1, 0, ready, gate);
    if (b == -1) {
        perror("fork");
        return 1;
    }
    close(ready[1]);
    close(gate[0]);
    char pair[2];
    if (read(ready[0], pair, 2) != 2) {
        perror("ready barrier");
        return 1;
    }
    close(ready[0]);
    if (write(gate[1], "GG", 2) != 2) {
        perror("gate");
        return 1;
    }
    close(gate[1]);
    puts("Both children hold one semaphore and wait on the other's semaphore "
         "(deadlock). Removing "
         "the set releases them.");
    sleep(1);
    if (semctl(id, 0, IPC_RMID) == -1)
        perror("IPC_RMID");
    while (wait(NULL) > 0) {
    }
    return 0;
}
