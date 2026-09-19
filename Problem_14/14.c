/*
 * Problem 14: Identifying a file type
 *
 * Problem statement: Accept a path from the command line and identify the type of file using file-status information.
 */

/* Opens the argument, obtains metadata with fstat(), and classifies the descriptor
 * using the S_IS* macros.  The matching file type is written directly to stdout.
 */


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Enter the name of the file as the argument\n");
        return 0;
    }
    
    int fd = open(argv[1], O_RDONLY);
    struct stat statbuf;

    fstat(fd, &statbuf);

    if (S_ISREG(statbuf.st_mode))
        write(STDOUT_FILENO, "Regular File\n", 13);
    else if (S_ISDIR(statbuf.st_mode))
        write(STDOUT_FILENO, "Directory File\n", 15);
    else if (S_ISCHR(statbuf.st_mode))
        write(STDOUT_FILENO, "Character File\n", 15);
    else if (S_ISBLK(statbuf.st_mode))
        write(STDOUT_FILENO, "Block File\n", 11);
    else if (S_ISFIFO(statbuf.st_mode))
        write(STDOUT_FILENO, "FIFO File\n", 10);
    else if (S_ISLNK(statbuf.st_mode))
        write(STDOUT_FILENO, "Symbolic Link File\n", 19);
    else if (S_ISSOCK(statbuf.st_mode))
        write(STDOUT_FILENO, "Socket\n", 7);
    else
        write(STDOUT_FILENO, "Error\n", 6);
    return 0;
}




