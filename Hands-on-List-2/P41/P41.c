/*
 * P41 / P41.c
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEYFILE "/tmp/oslab_sysv_msgq_key"
/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    int fd = open(KEYFILE, O_CREAT | O_RDWR, 0600);
    if (fd == -1) {
        perror("open key file");
        return EXIT_FAILURE;
    }
    close(fd);
    key_t key = ftok(KEYFILE, 'Q');
    if (key == (key_t)-1) {
        perror("ftok");
        return EXIT_FAILURE;
    }
    int id = msgget(key, IPC_CREAT | 0600);
    if (id == -1) {
        perror("msgget");
        return EXIT_FAILURE;
    }
    printf("Message queue key: %ld\nMessage queue ID: %d\n", (long)key, id);
    return EXIT_SUCCESS;
}
