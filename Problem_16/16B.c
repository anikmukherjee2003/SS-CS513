/*
 * Problem 16: Implementing a mandatory read lock
 *
 * Problem statement: Configure and apply a mandatory read lock to a file and report the locking operation.
 */

/* Requests an advisory read lock covering all of 16b.txt.  The flock structure
 * describes the range and lock type; input pauses the process before unlocking.
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(){

        struct flock fm;
        char s[100];
        int fq = open("16b.txt", O_RDWR | O_CREAT, 0666);
        fm.l_type = F_RDLCK;
        fm.l_whence = SEEK_SET;
        fm.l_start = 0;
        fm.l_len = 0;
        fm.l_pid = getpid();

        printf("Before locking the file for reading\n");
        fcntl(fq, F_SETLKW, &fm);
        printf("Read lock acquired successfully....\n");
        printf("Press a key to unlock...\n");
        getchar();

        fm.l_type = F_UNLCK;
        fcntl(fq, F_SETLK, &fm);
        printf("Finish\n");
        return 0;
}




