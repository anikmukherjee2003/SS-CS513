/*
 * Problem 17: Reserving a ticket with a write lock
 *
 * Problem statement: Open the ticket file, acquire a write lock, read and increment the ticket number, print the new number, and close the file.
 */

/* Opens the shared ticket file, obtains an exclusive advisory lock, increments the
 * stored integer, rewinds with lseek(), and writes it back.  getchar() holds the
 * critical section until the user releases the lock.
 */




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    struct flock fm = {0};
    int ticketno;

    int fq = open("ticket.txt", O_RDWR | O_CREAT, 0644);

    if (fq == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    fm.l_type = F_WRLCK;
    fm.l_whence = SEEK_SET;
    fm.l_start = 0;
    fm.l_len = 0;

    printf("Before entering the critical section...\n");
    fflush(stdout);

    if (fcntl(fq, F_SETLKW, &fm) == -1) {
        perror("fcntl lock");
        close(fq);
        return EXIT_FAILURE;
    }

    printf("Inside the critical section...\n");

    // Read only after acquiring the lock
    if (lseek(fq, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fq);
        return EXIT_FAILURE;
    }

    ssize_t n = read(fq, &ticketno, sizeof(ticketno));

    if (n != sizeof(ticketno)) {
        fprintf(stderr, "Could not read a complete ticket number\n");
        close(fq);
        return EXIT_FAILURE;
    }

    printf("Previous ticket number: %d\n", ticketno);

    ticketno++;

    if (lseek(fq, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fq);
        return EXIT_FAILURE;
    }

    n = write(fq, &ticketno, sizeof(ticketno));

    if (n != sizeof(ticketno)) {
        perror("write");
        close(fq);
        return EXIT_FAILURE;
    }

    printf("Current ticket number: %d\n", ticketno);
    printf("Press Enter to unlock and exit: ");
    fflush(stdout);

    getchar();

    fm.l_type = F_UNLCK;

    if (fcntl(fq, F_SETLK, &fm) == -1) {
        perror("fcntl unlock");
        close(fq);
        return EXIT_FAILURE;
    }

    close(fq);

    printf("Completed!!!\n");

    return EXIT_SUCCESS;
}





