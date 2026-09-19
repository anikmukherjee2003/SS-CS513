/*
 * Problem 13: Waiting for standard input with select()
 *
 * Problem statement: Wait up to 10 seconds for input on standard input using select() and report whether data became available or the wait timed out.
 */

/* Waits up to ten seconds for input on standard input.  select() updates readfds
 * and retval; available data is read with fgets(), while timeout/error paths report
 * the corresponding result.
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main() {

    fd_set readfds;
    struct timeval timeout;
    int retval;

    char buffer[100];
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for STDIN input for 10 seconds...\n");

    retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
        exit(EXIT_FAILURE);
    } else if (retval) {
        printf("Data is available. Enter your input: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Input received: %s", buffer);
        }
    } else {
        printf("No input received within the timeout period.\n");
    }

    return 0;
}




