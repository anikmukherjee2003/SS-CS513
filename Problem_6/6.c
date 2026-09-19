/*
 * Problem 6: Input and output using read() and write()
 *
 * Problem statement: Read input from standard input and display it on standard output using only the read() and write() system calls.
 */

/* Copies bytes from standard input (descriptor 0) to standard output (1).
 * read() fills the buffer once; a terminator is added for safety, while write()
 * emits exactly the bytes received.
 */


#include <stdio.h>
#include <unistd.h>

int main(){

    char buffer[1024];
    ssize_t bytesRead;

    bytesRead = read(0, buffer, sizeof(buffer)-1);// read(stdin, buffer, sizeof(buffer)-1) to leave space for null terminator

    if(bytesRead>0){
        buffer[bytesRead]= '\0';
        write(1, buffer, bytesRead);
    }
    printf("Bytes read: %zd\n", bytesRead);
    return 0;
}


/*OUTPUT:
anikm@ANIK:~/Hands-On-List1-Files/Problem_6$ gcc 6.c -o 6
anikm@ANIK:~/Hands-On-List1-Files/Problem_6$ ./6
Anik Mukherjee, MT2026007, Systems Software
Anik Mukherjee, MT2026007, Systems Software
Bytes read: 44
anikm@ANIK:~/Hands-On-List1-Files/Problem_6$
*/


