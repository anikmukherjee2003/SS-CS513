/*
 * P42 / common.h
 * Revision notes:
 *   - This header belongs to the OS lab collection and is designed for
 *     revision, tracing, and debugging of a single Linux programming concept.
 *   - Shared declarations and utilities used by the exercise family.
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

#ifndef OSLAB_P42_COMMON_H
#define OSLAB_P42_COMMON_H
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

struct sample_msg {
    long type;
    char text[16];
};

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static int inspect(char part) {

    int id = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
    struct sample_msg m = {.type = 1, .text = "sample"};
    struct msqid_ds ds;

    if (id == -1) {
        perror("msgget");
        return 1;
    }

    if (msgsnd(id, &m, sizeof m.text, 0) == -1) {
        perror("msgsnd");
        msgctl(id, IPC_RMID, NULL);
        return 1;
    }

    if (msgrcv(id, &m, sizeof m.text, 1, 0) == -1) {
        perror("msgrcv");
        msgctl(id, IPC_RMID, NULL);
        return 1;
    }

    if (msgctl(id, IPC_STAT, &ds) == -1) {
        perror("msgctl IPC_STAT");
        msgctl(id, IPC_RMID, NULL);
        return 1;
    }

    switch (part) {

    case 'a':
        printf("Access mode: %04o\n", ds.msg_perm.mode & 0777);
        break;

    case 'b':
        printf("Owner UID: %u\nOwner GID: %u\n", (unsigned)ds.msg_perm.uid,
               (unsigned)ds.msg_perm.gid);
        break;

    case 'c': {
        time_t st = ds.msg_stime, rt = ds.msg_rtime;
        struct tm stm, rtm;
        char sb[64], rb[64];
        localtime_r(&st, &stm);
        localtime_r(&rt, &rtm);
        strftime(sb, sizeof sb, "%Y-%m-%d %H:%M:%S", &stm);
        strftime(rb, sizeof rb, "%Y-%m-%d %H:%M:%S", &rtm);
        printf("Last send: %s\nLast receive: %s\n", sb, rb);
        break;
    }

    case 'd': {
        time_t ct = ds.msg_ctime;
        printf("Last queue change: %s", ctime(&ct));
        break;
    }

    case 'e':
        printf("Current queue size: %lu bytes\n",
               (unsigned long)ds.__msg_cbytes);
        break;

    case 'f':
        printf("Messages currently queued: %lu\n", (unsigned long)ds.msg_qnum);
        break;

    case 'g':
        printf("Maximum queue bytes: %lu\n", (unsigned long)ds.msg_qbytes);
        break;

    case 'h':
        printf("PID of last msgsnd: %ld\nPID of last msgrcv: %ld\n",
               (long)ds.msg_lspid, (long)ds.msg_lrpid);
        break;
    }

    msgctl(id, IPC_RMID, NULL);
    return 0;
}

#endif
