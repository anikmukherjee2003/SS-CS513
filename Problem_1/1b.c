/*
 * Problem 1: Creating a hard link
 *
 * Problem statement: Use the link() system call to create a hard link to an existing file and demonstrate that both directory entries refer to the same inode.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* target2 = original file that already exists */
    const char *target2 = "/home/anikm/Hands-On-List1-Files/Problem_1/hardlink.txt";

    /* linkPath2 = new hard link name */
    const char *linkPath2 = "/home/anikm/Hands-On-List1-Files/Problem_1/HardLink";

    /* link() creates a hard link.
     * If it fails, the program prints the error and exits.
     */
    int b = link(target2, linkPath2);
    if (b == -1) {
        perror("hard link failed");
        exit(1);
    }

    printf("Successfully created hard link\n");
    return 0;
}

