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

void print_file_info(const char *fileInfo){
    struct stat file_stat; 
    printf("\nFile: %s\n", fileInfo);
    printf("Inode: %ld\n",(long)file_stat.st_ino);
    printf("No. of hard links: %ld\n", (long)file_stat.st_nlink);
    printf("UID: %d\n", file_stat.st_uid);
    printf("GID: %d\n", file_stat.st_gid);
    printf("Size: %ld bytes\n", (long)file_stat.st_size);
    printf("Block Size: %ld bytes\n", (long)file_stat.st_blksize);
    printf("No. of Blocks: %ld\n",(long) file_stat.st_blocks);
    // Use the `ctime` function in `time.h` header to convert the timestamp in epoch to a more human readable form
	printf("Last Access: %s", ctime(&file_stat.st_atime));
	printf("Last Modification: %s", ctime(&file_stat.st_mtime));
	printf("Time of Last change: %s", ctime(&file_stat.st_ctime));
}

int main(){
    const char *fileInfo = "9.txt";
    print_file_info(fileInfo);
    return 0;
}





