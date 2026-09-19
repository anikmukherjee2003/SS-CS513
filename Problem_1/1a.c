/*
 * Problem 1: Creating a symbolic link
 *
 * Problem statement: Use the symlink() system call to create a soft link to an existing file and report the result.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* target1 = actual file we want to point to */
    const char *target1 = "/home/anikm/Hands-On-List1-Files/Problem_1/softlink.txt";

    /* linkPath1 = new link name that will appear in the directory */
    const char *linkPath1 = "/home/anikm/Hands-On-List1-Files/Problem_1/SoftLink";

    /* symlink() creates the symbolic link.
     * It returns -1 on failure, which we check with perror().
     */
    int a = symlink(target1, linkPath1);
    if (a == -1) {
        perror("soft link failed");
        exit(1);
    }

    printf("Successfully created soft link\n");
    return 0;
}



