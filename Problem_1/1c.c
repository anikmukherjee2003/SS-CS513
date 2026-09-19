/*
 * Problem 1: Creating a FIFO
 *
 * Problem statement: Create named pipes using the mkfifo() library function and the mknod() system call.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* Expect exactly two filenames: one for mkfifo and one for mknod */
    if (argc != 3) {
        printf("Enter 2 file names to create FIFO with mkfifo and mknod\n");
        return 0;
    }

    const char *mkfifoName = argv[1];
    const char *mknodName = argv[2];

    /* mkfifo() creates a FIFO with permissions S_IRWXU (owner can read/write/execute).
     * It is the usual API for named pipes.
     */
    int mkfifo_status = mkfifo(mkfifoName, S_IRWXU);
    if (mkfifo_status == -1) {
        perror("Error while creating FIFO file with mkfifo");
    } else {
        printf("Created FIFO file with mkfifo successfully\n");
    }

    /* mknod() can also create FIFO files by using the S_IFIFO type flag.
     * The third argument is a device number, which is ignored for FIFOs.
     */
    int mknod_status = mknod(mknodName, S_IFIFO | S_IRWXU, 0);
    if (mknod_status == -1) {
        perror("Error while creating FIFO file with mknod");
    } else {
        printf("Created FIFO file with mknod successfully\n");
    }

    return 0;
}

