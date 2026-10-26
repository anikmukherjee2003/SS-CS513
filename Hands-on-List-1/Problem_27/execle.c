/*
 * Problem 26: Executing ls -Rl with execle()
 *
 * Problem statement: Execute ls -Rl using the execle() system call and an explicit environment.
 */

/* Demonstrates execle(), which uses an absolute path, variadic arguments, and an
 * explicit environment pointer.  Successful process replacement does not return.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("===== Output using execled ======\n");
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, NULL);
    printf("\n");
    return 0;
}





