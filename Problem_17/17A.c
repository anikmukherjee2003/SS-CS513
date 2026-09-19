/*
 * Problem 17: Initializing the ticket file
 *
 * Problem statement: Open a ticket file, store an initial ticket number, and close the file for use by the reservation program.
 */

/* Reads an integer ticket number from the terminal and writes its binary value to
 * ticket.txt using open(), write(), and close().  The file descriptor is write-only.
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int ticketno;
	int file = open("ticket.txt", O_WRONLY);
	printf("Enter the Ticket number you want to store: ");
	scanf("%d", &ticketno);
	write(file, &ticketno, sizeof(ticketno));
	printf("Ticket number %d stored succesfully \n", ticketno);
	close(file);
	return 0;
}





