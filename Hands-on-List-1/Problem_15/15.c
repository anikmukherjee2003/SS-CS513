/*
 * Problem 15: Displaying environment variables
 *
 * Problem statement: Display the user's environment variables by traversing the environ variable.
 */

/* Walks the process environment exposed by the environ pointer and prints each
 * null-terminated NAME=VALUE entry until the array terminator is reached.
 */



#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}


