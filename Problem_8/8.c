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
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    ssize_t n;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while ((n = read(fd, &ch, 1)) > 0) {
        if (write(STDOUT_FILENO, &ch, 1) != 1) {
            perror("write");
            close(fd);
            return 1;
        }
    }

    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

