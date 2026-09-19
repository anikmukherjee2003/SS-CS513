/*
 * Problem 26: Executing ls -Rl with execl()
 *
 * Problem statement: Execute ls -Rl using the execl() system call.
 */

/* Demonstrates execl(): an absolute executable path is supplied with a variadic
 * argument list.  A successful exec never returns, so the following printf is
 * reached only if replacement fails.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("===== Output using execl =====\n");
    execl("/bin/ls", "ls", "-Rl", (char *)NULL);
    printf("\n");
    return 0;
}






