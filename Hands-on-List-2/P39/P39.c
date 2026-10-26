/*
 * P39 / P39.c
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

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Main entry point for this exercise.
 * The function sets up the required resources, invokes the relevant OS
 * operation, checks return values, and cleans up before exiting.
 */
int main(int argc, char **argv) {

    const char *p = argc > 1 ? argv[1] : "/tmp/oslab_p39_fifo";

    int fd;

    fd_set set;

    struct timeval tv =
        {

            .tv_sec = 10, .tv_usec = 0}

    ;

    char b[256];

    if (mkfifo(p, 0600) == -1 && errno != EEXIST) {

        perror("mkfifo");

        return EXIT_FAILURE;
    }

    /* Linux O_RDWR prevents immediate EOF before a writer appears. */ fd =
        open(p, O_RDWR | O_NONBLOCK);

    if (fd == -1) {

        perror("open");

        return EXIT_FAILURE;
    }

    printf("Waiting up to 10 seconds for data on %s...\n", p);

    fflush(stdout);

    FD_ZERO(&set);

    FD_SET(fd, &set);

    int ready = select(fd + 1, &set, NULL, NULL, &tv);

    if (ready == -1) {

        perror("select");

        close(fd);

        return EXIT_FAILURE;
    }

    if (ready == 0) {

        puts("Timed out without data.");

        close(fd);

        return EXIT_SUCCESS;
    }

    ssize_t n = read(fd, b, sizeof b - 1);

    if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
        puts("No bytes were available.");

    else if (n == -1)
        perror("read");

    else {

        b[n] = '\0';

        printf("Received: %s\n", b);
    }

    close(fd);

    return EXIT_SUCCESS;
}
