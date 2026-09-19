/*
 * Problem 8: Reading a file line by line
 *
 * Problem statement: Open a file in read-only mode, read and display it line by line, and close it when end-of-file is reached.
 */

/* Reads a file one byte at a time and writes each complete line to stdout.
 * line_buffer and line_index accumulate input, with MAX_LINE_LENGTH preventing
 * overflow; a final unterminated line is emitted after EOF.
 */


#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 2048

int main(int argc, char *argv[]) {
    int fd;
    char char_buffer; //used to read one char at a time
    ssize_t bytes_read;

    char line_buffer[MAX_LINE_LENGTH]; // buffer for current line
    int line_index = 0; 

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; 
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    while ((bytes_read = read(fd, &char_buffer, 1)) > 0) {
        line_buffer[line_index] = char_buffer;
        line_index++;


        if (char_buffer == '\n') {
            write(1, line_buffer, line_index);
            line_index = 0;
        }

        if (line_index >= MAX_LINE_LENGTH) {
            write(1, line_buffer, line_index);
            line_index = 0;
        }
    }
    
    if (line_index > 0) {
        write(1, line_buffer, line_index);
    }

    if (bytes_read == -1) {
        perror("Error reading from file");
    }

    close(fd);

    return 0;
}

