/*
 * Problem 10: Writing data and seeking in a file
 *
 * Problem statement: Write 10 bytes to a file, move the file pointer forward by 10 bytes with lseek(), write another 10 bytes, check the return value, and inspect the resulting holes with od.
 */

/* Creates/truncates 10.txt, writes two ten-byte buffers, then uses lseek() to
 * skip ten bytes between them.  fd is the file descriptor and offset records the
 * resulting file position; all I/O failures close the descriptor before exit.
 */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    off_t offset;
    char buff1[10] = "AAYANKIONK";   // first 10 B
    char buff2[10] = "0202111199";   // next 10  B

    // open file in read-write mode (create if not exists, truncate if exists)
    fd = open("10.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    
    if (write(fd, buff1, 10) != 10) { //10B written
        perror("Write in Buff1");
        close(fd);
        exit(1);
    }

    
    offset = lseek(fd, 10, SEEK_CUR);  //moving by 10B
    if (offset == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }

    printf("lseek Return Value (new offset): %ld\n", (long)offset);

    // write second 10 bytes
    if (write(fd, buff2, 10) != 10) {
        perror("Write in Buff2");
        close(fd);
        exit(1);
    }

    close(fd);
    return 0;
}






