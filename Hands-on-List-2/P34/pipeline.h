/*
 * P34 / pipeline.h
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

#ifndef OSLAB_P34_PIPELINE_H
#define OSLAB_P34_PIPELINE_H
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { USE_DUP = 1, USE_DUP2 = 2, USE_FCNTL = 3 };

/*
 * Helper routine: this function encapsulates part of the exercise logic
 * so the surrounding call flow stays readable and easy to trace.
 */
static int redirect_fd(int oldfd, int target, int method) {

    if (method == USE_DUP2)
        return dup2(oldfd, target) == target ? 0 : -1;

    if (method == USE_DUP) {

        if (close(target) == -1 && errno != EBADF)
            return -1;

        return dup(oldfd) == target ? 0 : -1;
    }

    if (close(target) == -1 && errno != EBADF)
        return -1;

    return fcntl(oldfd, F_DUPFD, target) == target ? 0 : -1;
}

static int run_pipeline(int method) {

    int fd[2], status1, status2;

    pid_t ls, wc;

    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    ls = fork();

    if (ls == -1) {
        perror("fork ls");
        return EXIT_FAILURE;
    }

    if (ls == 0) {

        close(fd[0]);

        if (redirect_fd(fd[1], STDOUT_FILENO, method) == -1) {
            perror("redirect stdout");
            _exit(126);
        }

        close(fd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);

        perror("exec ls");
        _exit(127);
    }

    wc = fork();

    if (wc == -1) {
        perror("fork wc");
        close(fd[0]);
        close(fd[1]);
        waitpid(ls, NULL, 0);
        return EXIT_FAILURE;
    }

    if (wc == 0) {

        close(fd[1]);

        if (redirect_fd(fd[0], STDIN_FILENO, method) == -1) {
            perror("redirect stdin");
            _exit(126);
        }

        close(fd[0]);

        execlp("wc", "wc", (char *)NULL);

        perror("exec wc");
        _exit(127);
    }

    close(fd[0]);
    close(fd[1]);

    if (waitpid(ls, &status1, 0) == -1 || waitpid(wc, &status2, 0) == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return (WIFEXITED(status1) && WEXITSTATUS(status1) == 0 &&
            WIFEXITED(status2) && WEXITSTATUS(status2) == 0)
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}

#endif
