/*
 * Problem 25: Receiving input from an exec-ed program
 *
 * Problem statement: Act as the executable target for the exec exercise and display the name passed in argv.
 */

/* Small exec target that prints argv[1].  argc/argv contain the command-line
 * arguments supplied by the caller, such as Problem_26/26.c.
 */



#include <stdio.h>

int main(int argc, char *argv[]) {
    
    printf("Hello, My name is %s!\n", argv[1]);
    return 0;
}




