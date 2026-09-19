/*
 * Problem 3: Creating a file and printing its descriptor
 *
 * Problem statement: Create a file with creat() and print the file descriptor returned by the system call.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    /* Name of the file to create */
    const char *file_path = "anik.txt";

    /* 0644 means rw-r--r--
     * - owner: read/write
     * - group: read only
     * - others: read only
     */
    mode_t mode = 0644;

    /* creat() creates the file if it doesn't already exist.
     * It opens it for writing and returns a file descriptor.
     */
    int fd = creat(file_path, mode);

    printf("File descriptor: %d\n", fd);
    return 0;
}


/*OUTPUT: 
anikm@ANIK:~/Hands-On-List1-Files/Problem_3$ ./3
File descriptor: 3
anikm@ANIK:~/Hands-On-List1-Files/Problem_3$ ls -li
total 20
41394 -rwxr-xr-x 1 anikm anikm 15992 Sep 19 06:50 3
41392 -rwxrwxrwx 1 anikm anikm   597 Sep 19 06:50 3.c
41419 -rw-r--r-- 1 anikm anikm     0 Sep 19 06:50 anik.txt
*/