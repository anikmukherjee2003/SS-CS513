/*
 * P47 / P47b.c
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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEYFILE "/tmp/oslab_sysv_shm_key"
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    key_t k = ftok(KEYFILE, 'S');
    if (k == (key_t)-1) {
        perror("ftok; run P47a first");
        return 1;
    }
    int id = shmget(k, 4096, 0);
    if (id == -1) {
        perror("shmget; run P47a first");
        return 1;
    }
    const char *p = shmat(id, NULL, SHM_RDONLY);
    if (p == (void *)-1) {
        perror("shmat SHM_RDONLY");
        return 1;
    }
    printf("Read-only mapping contains: %s\n", p);
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        shmdt(p);
        return 1;
    }
    if (child == 0) {
        struct rlimit no_core = {0, 0};
        setrlimit(RLIMIT_CORE, &no_core);
        volatile char *q = (volatile char *)p;
        q[0] = 'X';
        _exit(0);
    }
    int status;
    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        shmdt(p);
        return 1;
    }
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
        puts("The child could not overwrite the SHM_RDONLY mapping (SIGSEGV).");
    else
        puts("The child write unexpectedly completed.");
    shmdt(p);
    return 0;
}
