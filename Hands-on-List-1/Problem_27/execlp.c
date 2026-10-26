/*
 * Problem 26: Executing ls -Rl with execlp()
 *
 * Problem statement: Execute ls -Rl using the execlp() system call.
 */

/* Demonstrates execlp(), which searches PATH for ls and passes -Rl through its
 * variadic argument list.  Code after the call runs only if exec fails.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("======== Output using execlp =============\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);
    printf("\n");
    return 0;
}





