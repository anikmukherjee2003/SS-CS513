/*
 * Problem 17: Reserving a ticket with a write lock
 *
 * Problem statement: Open the ticket file, acquire a write lock, read and increment the ticket number, print the new number, and close the file.
 */

/* Opens the shared ticket file, obtains an exclusive advisory lock, increments the
 * stored integer, rewinds with lseek(), and writes it back.  getchar() holds the
 * critical section until the user releases the lock.
 */



#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	struct flock fm;
	int ticketno;

	int fq = open("ticket.txt", O_RDWR | O_CREAT);

	if(fq == -1){
		printf("Error: Could not open the file\n");
	}
	else{
		read(fq, &ticketno, sizeof(ticketno));
		fm.l_type = F_WRLCK;
		fm.l_whence = SEEK_SET;
		fm.l_start = 0;
		fm.l_len = 0;
		fm.l_pid = getpid();

		printf("Before entering the critical section...\n");
		fcntl(fq, F_SETLKW, &fm);
		printf("Inside the critical section...\n");
        printf("Previous ticket number: %d\n", ticketno);
		ticketno++;
		printf("Current ticket number: %d\n", ticketno);

		lseek(fq, 0, SEEK_SET);
		write(fq, &ticketno, sizeof(ticketno));
		printf("Press any key to unlock and exit");
		getchar();

		fm.l_type = F_UNLCK;
		fcntl(fq, F_SETLK, &fm);
		close(fq);
		printf("Completed!!!\n");
	}
	return 0;
}






