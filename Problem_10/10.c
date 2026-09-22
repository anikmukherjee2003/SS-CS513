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
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;
    char buff1[] = "ANIK3IIITB";
    char buff2[] = "SYSTEMSLAB!";

    // Create/open file and clear old contents
    fd = open("sparse.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write first 10 bytes
    if (write(fd, buff1, 10) != 10) {
        perror("write");
        close(fd);
        return 1;
    }

    // Move file offset directly to byte 20
    if (lseek(fd, 20, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Write next 10 bytes
    if (write(fd, buff2, 10) != 10) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Sparse file created successfully.\n");

    close(fd);
    return 0;
}

/*
anikm@ANIK:~/Hands-On-List1-Files/Problem_10$ ./10
Sparse file created successfully.
anikm@ANIK:~/Hands-On-List1-Files/Problem_10$ stat sparse.txt
  File: sparse.txt
  size: 30              Blocks: 8          IO Block: 4096   regular file
Device: 8,48    Inode: 1739        Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/   anikm)   Gid: ( 1000/   anikm)
Access: 2026-09-21 17:28:24.278042906 +0000
Modify: 2026-09-21 17:28:15.774044989 +0000
Change: 2026-09-21 17:28:15.774044989 +0000
 Birth: 2026-09-21 17:27:27.690058271 +0000
anikm@ANIK:~/Hands-On-List1-Files/Problem_10$ od -c sparse.txt
0000000   A   N   I   K   3   I   I   I   T   B  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   S   Y   S   T   E   M   S   L   A   B
0000036
*/




