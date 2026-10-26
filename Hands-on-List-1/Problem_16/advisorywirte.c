/*
 * Problem 16: Implementing a mandatory write lock
 *
 * Problem statement: Configure and apply a mandatory write lock to a file and report the locking operation.
 */

/* Requests an advisory write lock covering all of 16.txt with fcntl(F_SETLKW).
 * The process blocks until the lock is available, waits for a key, then releases
 * it with F_SETLK.
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main(void)
{
    int fd = open("16.txt", O_RDWR | O_CREAT, 0666);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    printf("Requesting write lock...\n");
    fflush(stdout);

    // Acquire exclusive lock (wait if another lock blocks it)
    if (flock(fd, LOCK_EX | LOCK_NB)  == -1) {
        perror("flock");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Write lock acquired!\n");
    printf("Press Enter to release the lock...\n");
    getchar();

    // Release the lock
    if (flock(fd, LOCK_UN) == -1) {
        perror("flock unlock");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Write lock released.\n");

    close(fd);
    return EXIT_SUCCESS;
}
