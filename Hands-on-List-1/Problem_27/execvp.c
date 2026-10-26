/*
 * Problem 26: Executing ls -Rl with execvp()
 *
 * Problem statement: Execute ls -Rl using the execvp() system call.
 */

/* Demonstrates execvp(), combining PATH lookup with an argv array for ls -Rl.
 * A successful call replaces the process and therefore does not return.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("======== Output using execvp ========== \n");
    char *argv[] = {"ls", "-Rl", NULL};
    execvp("ls", argv);
    printf("\n");
    return 0;
}



