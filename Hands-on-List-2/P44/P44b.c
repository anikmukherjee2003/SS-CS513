/*
 * P44 / P44b.c
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
#include <sys/msg.h>

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
    key_t k = ftok(KEYFILE, 'Q');
    if (k == (key_t)-1) {
        perror("ftok; run P41 first");
        return 1;
    }
    int id = msgget(k, 0);
    if (id == -1) {
        perror("msgget; run P41 first");
        return 1;
    }
    struct msg m;
    if (msgrcv(id, &m, sizeof m.text, 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            puts("Queue is empty; IPC_NOWAIT returned immediately.");
            return 0;
        }
        perror("msgrcv");
        return 1;
    }
    printf("Received (IPC_NOWAIT): %s\n", m.text);
    return 0;
}
