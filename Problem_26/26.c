/*
 * Problem 25: Executing an executable with exec
 *
 * Problem statement: Execute another program with an exec function and pass a name argument as command-line input.
 */

/* Replaces this process with ./a.out via execvp().  command and args provide the
 * executable name and one name argument; a return from execvp() indicates failure.
 */


#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main() {
    char *command = "./a.out";
    char *name = "Aayank Singhai (MT2025001)";
    char *args[] = {command, name, NULL};

    execvp(command, args);
    return 1;
}




