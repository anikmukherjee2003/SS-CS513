/*
 * Problem 16: Implementing a mandatory read lock
 *
 * Problem statement: Configure and apply a mandatory read lock to a file and report the locking operation.
 */

/* Requests an advisory read lock covering all of 16b.txt.  The flock structure
 * describes the range and lock type; input pauses the process before unlocking.
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("16.txt", O_RDONLY | O_CREAT, 0666);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Traditional mandatory-locking permission setup
    if (fchmod(fd, S_ISGID | S_IRUSR | S_IWUSR) == -1) {
        perror("fchmod");
        close(fd);
        return EXIT_FAILURE;
    }

    struct flock lock = {0};

    lock.l_type = F_RDLCK;      // Read lock
    lock.l_whence = SEEK_SET;   // Start relative to file beginning
    lock.l_start = 0;           // Start at byte 0
    lock.l_len = 0;             // Lock through EOF

    printf("Requesting read lock...\n");
    fflush(stdout);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl lock");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Read lock acquired!\n");
    printf("Press Enter to release the lock...\n");
    getchar();

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Read lock released.\n");

    close(fd);
    return EXIT_SUCCESS;
}



