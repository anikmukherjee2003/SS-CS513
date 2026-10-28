/*
 * P43 / P43.c
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
#include <sys/msg.h>
#include <unistd.h>

#define KEYFILE "/tmp/oslab_sysv_msgq_key"
struct msg {
    long type;
    char text[128];
};

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
    key_t k = ftok(KEYFILE, 'Q');
    if (k == (key_t)-1) {
        perror("ftok");
        return 1;
    }
    int id = msgget(k, IPC_CREAT | 0600);
    if (id == -1) {
        perror("msgget");
        return 1;
    }
    struct msg m = {.type = 1};
    snprintf(m.text, sizeof m.text, "Message sent by P43 (PID %ld)",
             (long)getpid());
    if (msgsnd(id, &m, strlen(m.text) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }
    printf("Sent: %s\nQueue ID: %d\nInspect with: ipcs -q\n", m.text, id);
    return 0;
}
