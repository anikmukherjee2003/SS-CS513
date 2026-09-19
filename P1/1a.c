/*
 * Problem 1: Creating a symbolic link
 *
 * Problem statement: Use the symlink() system call to create a soft link to an existing file and report the result.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    const char *target1 = "/home/anikm/Hands-On-List1-Files/P1/softlink.txt";
    const char *linkPath1 = "/home/anikm/Hands-On-List1-Files/P1/SoftLink";
    int a = symlink(target1,linkPath1); //creating soft link
    if(a == -1){
        perror("soft link failed\n");
        exit(1);
    }
    printf("Sucessfully Soft link created\n");

    return 0;
}






