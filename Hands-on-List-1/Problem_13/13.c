/*
 * Problem 13: Waiting for standard input with select()
 *
 * Problem statement: Wait up to 10 seconds for input on standard input using select() and report whether data became available or the wait timed out.
 */

/* Waits up to ten seconds for input on standard input. select() checks whether
 * stdin is readable; on timeout it reports the timeout, on readiness it reads a
 * line with fgets(), and on error it reports the failure.
 */




#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    fd_set readfds;
    struct timeval timeout;
    char buffer[100];

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting up to 10 seconds for input...\n");
    fflush(stdout);

    int retval = select(STDIN_FILENO + 1,
                        &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        if (errno == EINTR) {
            printf("select() was interrupted by a signal.\n");
        } else {
            perror("select");
        }
        return EXIT_FAILURE;
    }

    if (retval == 0) {
        printf("Timed out: no input became available.\n");
        return EXIT_SUCCESS;
    }

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        printf("Standard input is ready.\n");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Input received: %s", buffer);
        } else {
            printf("No readable line could be obtained (EOF or error).\n");
        }
    }

    return EXIT_SUCCESS;
}




