/*
 * Problem 16: Implementing a mandatory write lock
 *
 * Problem statement: Configure and apply a mandatory write lock to a file and report the locking operation.
 */

/* Requests an advisory write lock covering all of 16.txt with fcntl(F_SETLKW).
 * The process blocks until the lock is available, waits for a key, then releases
 * it with F_SETLK.
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(){

	struct flock fm;
	char s[100];
	int fq = open("16.txt", O_RDWR | O_CREAT, 0666);
	fm.l_type = F_WRLCK;
	fm.l_whence = SEEK_SET;
	fm.l_start = 0;
	fm.l_len = 0;
	fm.l_pid = getpid();
	printf("Before locking the file for writing\n");
	fcntl(fq, F_SETLKW, &fm);
	printf("Write lock acquired successfully....\n");
	printf("Press a key to unlock...\n");
	getchar();
	fm.l_type = F_UNLCK;
	fcntl(fq, F_SETLK, &fm);
	printf("Finish\n");
	return 0;
}

