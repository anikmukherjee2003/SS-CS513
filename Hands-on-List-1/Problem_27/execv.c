/*
 * Problem 26: Executing ls -Rl with execv()
 *
 * Problem statement: Execute ls -Rl using the execv() system call and an argument vector.
 */

/* Demonstrates execv() with an absolute path and an argv array containing ls -Rl.
 * The current process image is replaced when the call succeeds.
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("========== Output using execv ===========\n");
    char *argv[] = {"ls", "-Rl", NULL};
    execv("/bin/ls", argv);
    return 0;
}



