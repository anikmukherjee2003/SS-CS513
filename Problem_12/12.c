/*
 * Problem 12: Determining a file opening mode
 *
 * Problem statement: Use fcntl() to determine the access mode with which a file was opened.
 */

/* Opens the filename argument and queries its access/status flags with fcntl().
 * O_ACCMODE selects the access mode before the switch reports the matching value.
 */


/*
STATUS CODE MAPPING

                    0    = O_RDONLY
                    1    = O_WRONLY
                    2    = O_RDWR
                    64   = O_CREAT
                    512  = O_TRUNC
                    1024 = O_APPEND
                    577  = O_WRONLY | O_CREAT | O_TRUNC
                    1089 = O_WRONLY | O_CREAT | O_APPEND
                    578  = O_RDWR   | O_CREAT | O_TRUNC
                    1090 = O_RDWR   | O_CREAT | O_APPEND
*/


#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		perror("Enter File Name: \n");
		return 0;
	}
	int fd = open(argv[1],O_RDWR);
	if(fd == -1){
		perror("Error while opening file\n");
		return 0;
	}
	
	int status = fcntl(fd,F_GETFL);
	if(status == -1){
		printf("ERROR in fetching Status\n");
		return 0;
	}
	 
	switch (O_ACCMODE & status){
        case 0:
            printf("The file has been opened with the flags : O_RDONLY\n");
            break;
        case 1:
            printf("The file has been opened with the flags : O_WRONLY\n");
            break;
        case 2:
            printf("The file has been opened with the flags : O_RDWR\n");
            break;
        case 64:
            printf("The file has been opened with the flags : O_CREAT\n");
            break;
        case 512:
            printf("The file has been opened with the flags : O_TRUNC\n");
            break;
        case 1024:
            printf("The file has been opened with the flags : O_APPEND\n");
            break;
        case 577:
            printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_TRUNC\n");
            break;
        case 1089:
            printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_APPEND\n");
            break;
        case 578:
            printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_TRUNC\n");
        	break;
        case 1090:
            printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_APPEND\n");
            break;
        default:
            printf("Error!");
        }
	return 0;	
}


