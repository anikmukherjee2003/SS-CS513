
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("16.txt", O_RDWR | O_CREAT, 0666);

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

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Requesting write lock...\n");
    fflush(stdout);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Write lock acquired. Press Enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("unlock");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Lock released.\n");
    close(fd);

    return EXIT_SUCCESS;
}