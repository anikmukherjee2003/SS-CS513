/*
 * P35 / P35.c
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
#include <sys/wait.h>
#include <unistd.h>

static int connect_fd(int source, int target) {

    if (dup2(source, target) == -1) {

        perror("dup2");

        return -1;
    }

    return 0;
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {

    int ls_to_grep[2], grep_to_wc[2];

    int ls_status, grep_status, wc_status;

    pid_t ls_pid, grep_pid, wc_pid;

    if (pipe(ls_to_grep) == -1 || pipe(grep_to_wc) == -1) {

        perror("pipe");

        return EXIT_FAILURE;
    }

    ls_pid = fork();

    if (ls_pid == -1) {
        perror("fork ls");
        return EXIT_FAILURE;
    }

    if (ls_pid == 0) {

        close(ls_to_grep[0]);

        close(grep_to_wc[0]);

        close(grep_to_wc[1]);

        if (connect_fd(ls_to_grep[1], STDOUT_FILENO) == -1)
            _exit(126);

        close(ls_to_grep[1]);

        execlp("ls", "ls", "-l", (char *)NULL);

        perror("exec ls");

        _exit(127);
    }

    grep_pid = fork();

    if (grep_pid == -1) {
        perror("fork grep");
        return EXIT_FAILURE;
    }

    if (grep_pid == 0) {

        close(ls_to_grep[1]);

        close(grep_to_wc[0]);

        if (connect_fd(ls_to_grep[0], STDIN_FILENO) == -1 ||
            connect_fd(grep_to_wc[1], STDOUT_FILENO) == -1)
            _exit(126);

        close(ls_to_grep[0]);

        close(grep_to_wc[1]);

        execlp("grep", "grep", "^d", (char *)NULL);

        perror("exec grep");

        _exit(127);
    }

    wc_pid = fork();

    if (wc_pid == -1) {
        perror("fork wc");
        return EXIT_FAILURE;
    }

    if (wc_pid == 0) {

        close(ls_to_grep[0]);

        close(ls_to_grep[1]);

        close(grep_to_wc[1]);

        if (connect_fd(grep_to_wc[0], STDIN_FILENO) == -1)
            _exit(126);

        close(grep_to_wc[0]);

        execlp("wc", "wc", "-l", (char *)NULL);

        perror("exec wc");

        _exit(127);
    }

    close(ls_to_grep[0]);

    close(ls_to_grep[1]);

    close(grep_to_wc[0]);

    close(grep_to_wc[1]);

    if (waitpid(ls_pid, &ls_status, 0) == -1 ||
        waitpid(grep_pid, &grep_status, 0) == -1 ||
        waitpid(wc_pid, &wc_status, 0) == -1) {

        perror("waitpid");

        return EXIT_FAILURE;
    }

    /* grep exits with status 1 when there are no directories; wc still
     * correctly prints 0. */
    int grep_ok = WIFEXITED(grep_status) && (WEXITSTATUS(grep_status) == 0 ||
                                             WEXITSTATUS(grep_status) == 1);

    return WIFEXITED(ls_status) && WEXITSTATUS(ls_status) == 0 && grep_ok &&
                   WIFEXITED(wc_status) && WEXITSTATUS(wc_status) == 0
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}
