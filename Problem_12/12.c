/*
 * Problem 12: Determining a file opening mode
 *
 * Problem statement: Use fcntl() to determine the access mode with which a file was opened.
 */

/*
 * Opens the filename passed as argv[1], then uses fcntl(F_GETFL) to query the
 * file status flags. The access mode is obtained with O_ACCMODE, which masks
 * out the read/write access bits from the remaining status flags.
 *
 * Access mode values:
 *   O_RDONLY = 0
 *   O_WRONLY = 1
 *   O_RDWR   = 2
 *
 * Common status flag values:
 *   O_CREAT = 64
 *   O_TRUNC = 512
 *   O_APPEND = 1024
 *
 * Example combined flags:
 *   O_WRONLY | O_CREAT | O_TRUNC = 577
 *   O_WRONLY | O_CREAT | O_APPEND = 1089
 *   O_RDWR   | O_CREAT | O_TRUNC = 578
 *   O_RDWR   | O_CREAT | O_APPEND = 1090
 */



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    // Extract access mode
    int mode = flags & O_ACCMODE;

    if (mode == O_RDONLY)
        printf("Access mode: O_RDONLY\n");
    else if (mode == O_WRONLY)
        printf("Access mode: O_WRONLY\n");
    else if (mode == O_RDWR)
        printf("Access mode: O_RDWR\n");

    // Check additional status flags
    if (flags & O_APPEND)
        printf("Status flag: O_APPEND\n");

    if (flags & O_NONBLOCK)
        printf("Status flag: O_NONBLOCK\n");

    if (flags & O_SYNC)
        printf("Status flag: O_SYNC\n");

    close(fd);
    return 0;
}


