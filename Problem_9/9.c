/*
 * Problem 9: Extracting file information
 *
 * Problem statement: Print a file's inode, hard-link count, UID, GID, size, block size, block count, and access, modification, and change times.
 */

/* Prints metadata for 9.txt using stat fields (inode, links, ownership, size,
 * blocks, and timestamps).  ctime() converts each stored epoch time for display.
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat info;

    // Check whether filename was provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file metadata
    if (stat(argv[1], &info) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Inode number: %ld\n", (long)info.st_ino);
    printf("Number of hard links: %ld\n", (long)info.st_nlink);
    printf("User ID: %ld\n", (long)info.st_uid);
    printf("Group ID: %ld\n", (long)info.st_gid);
    printf("File size: %ld bytes\n", (long)info.st_size);
    printf("Preferred block size: %ld bytes\n",
           (long)info.st_blksize);
    printf("Allocated blocks: %ld\n", (long)info.st_blocks);

    printf("Last access: %s", ctime(&info.st_atime));
    printf("Last modification: %s", ctime(&info.st_mtime));
    printf("Last status change: %s", ctime(&info.st_ctime));

    return 0;
}




