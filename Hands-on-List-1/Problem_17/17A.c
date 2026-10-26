/*
 * Problem 17: Initializing the ticket file
 *
 * Problem statement: Open a ticket file, store an initial ticket number, and close the file for use by the reservation program.
 */

/* Reads an integer ticket number from the terminal and writes its binary value to
 * ticket.txt using open(), write(), and close().  The file descriptor is write-only.
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int ticketno;

    int file = open("ticket.txt",
                    O_WRONLY | O_CREAT | O_TRUNC,
                    0644);

    if (file == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    printf("Enter the Ticket number you want to store: ");

    if (scanf("%d", &ticketno) != 1) {
        fprintf(stderr, "Invalid ticket number\n");
        close(file);
        return EXIT_FAILURE;
    }

    ssize_t bytes = write(file, &ticketno, sizeof(ticketno));

    if (bytes != sizeof(ticketno)) {
        perror("write");
        close(file);
        return EXIT_FAILURE;
    }

    printf("Ticket number %d stored successfully\n", ticketno);

    if (close(file) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}





