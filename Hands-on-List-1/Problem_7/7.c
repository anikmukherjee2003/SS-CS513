/*
 * Problem 7: Copying a file with system calls
 *
 * Problem statement: Copy the contents of file1 into file2, emulating the behavior of the cp file1 file2 command.
 */

/* Copies a source file to a destination in BUFFER_SIZE chunks.  open(), read(),
 * write(), and close() provide the file I/O; the destination is created/truncated.
 * Command-line validation and each open/write failure stop the operation safely.
 */


#include <stdio.h>    
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    
    int source_file, destination_file;
    
    ssize_t bytes_read; //no of bytes read from file
    char buffer[BUFFER_SIZE]; //temp storage to hold data

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1; 
    }

    source_file = open(argv[1], O_RDONLY); //opening in read only
    if (source_file == -1) {
        perror("Error opening source file");
        return 1;
    }

    destination_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_file == -1) {
        perror("Error creating destination file");
        close(source_file); //closing the already opened
        return 1;
    }

    while ((bytes_read = read(source_file, buffer, BUFFER_SIZE)) > 0) {
        if (write(destination_file, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(source_file);

            close(destination_file);
            return 1;
        }
    }
    close(source_file);
    close(destination_file);

    printf("File copied successfully!\n");

    return 0;

}

/*OUTPUT:

anikm@ANIK:~/Hands-On-List1-Files/Problem_7$ ./7
Usage: ./7 <source_file> <destination_file>
anikm@ANIK:~/Hands-On-List1-Files/Problem_7$ ./7 src.txt dest.txt
File copied successfully!
anikm@ANIK:~/Hands-On-List1-Files/Problem_7$ cat dest.txt
Contents written in source file.
Anik Mukherjee MT2026007 

*/


