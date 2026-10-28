/*
 * P36 / P36c.c
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

static int trace(const char *cmd, const char *path,
                 int m) { //'m' is flag which tell whether to add 'p' at the end
    pid_t p = fork();
    int s;
    if (p == -1) {
        perror("fork");
        return -1;
    }
    if (p == 0) {
        if (m)
            execlp("strace", "strace", "-c", "-e", "trace=mknod,mknodat", cmd,
                   path, "p", (char *)NULL);
        else
            execlp("strace", "strace", "-c", "-e", "trace=mknod,mknodat", cmd,
                   path, (char *)NULL);
        perror("exec strace (install strace if missing)");
        _exit(127);
    }
    if (waitpid(p, &s, 0) == -1) {
        perror("waitpid");
        return -1;
    }
    return WIFEXITED(s) ? WEXITSTATUS(s) : 128;
}

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(void) {
    char a[80], b[80];
    snprintf(a, sizeof a, "/tmp/oslab_mknod_%ld",
             (long)getpid()); // generate FIFO name a=/tmp/oslab_mknod_<PID>
    snprintf(b, sizeof b, "/tmp/oslab_mkfifo_%ld",
             (long)getpid()); // generate FIFO name b=/tmp/oslab_mkfifo_<PID>
    puts("System-call summary for mknod:");
    if (trace("mknod", a, 1) !=
        0) // falg m = 1, means mknod /tmp/oslab_mknod_<PID> p
        return EXIT_FAILURE;
    puts("System-call summary for mkfifo:");
    if (trace("mkfifo", b, 0) != 0) {
        unlink(a);
        return EXIT_FAILURE;
    }
    puts("Compare syscall counts and elapsed time; results depend on this "
         "machine and its "
         "utilities.");
    unlink(a);
    unlink(b);
    return EXIT_SUCCESS;
}
