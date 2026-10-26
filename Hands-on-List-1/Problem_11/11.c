/*
 * Problem 11: Duplicating file descriptors and appending
 *
 * Problem statement: Open a file, duplicate its descriptor with dup(), dup2(), and fcntl(), append data through the descriptors, and verify the file contents.
 */

/* Appends four messages through the original file descriptor and through
 * duplicates created with dup(), dup2(), and fcntl(F_DUPFD). All duplicates
 * share the same open-file description, so writes are appended to the same file
 * offset. The helper then reopens the file and reads it back to display the
 * final contents.
 */




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define FILENAME "11.txt"

void write_message(int fd, const char *message)
{
    size_t len = strlen(message);
    ssize_t written = write(fd, message, len);

    if (written == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    if ((size_t)written != len) {
        fprintf(stderr, "Partial write occurred\n");
        exit(EXIT_FAILURE);
    }
}

void display_file(void)
{
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    ssize_t n;

    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, n) != n) {
            perror("write to stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (n == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(void)
{
    // Open file in append mode
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // 1. Write using original descriptor
    write_message(fd, "Original FD: Hello!\n");

    // 2. Duplicate using dup()
    int fd1 = dup(fd); //new descriptor created by dup()
    if (fd1 == -1) {
        perror("dup");
        close(fd);
        return EXIT_FAILURE;
    }

    write_message(fd1, "dup FD: Hello!\n");

    // 3. Duplicate using dup2()
    int fd2 = dup2(fd, 10);//we are specifying the new descriptor number as 10
    if (fd2 == -1) {
        perror("dup2");
        close(fd);
        close(fd1);
        return EXIT_FAILURE;
    }

    write_message(fd2, "dup2 FD: Hello!\n");

    // 4. Duplicate using fcntl()
    int fd3 = fcntl(fd, F_DUPFD, 11);
    if (fd3 == -1) {
        perror("fcntl");
        close(fd);
        close(fd1);
        close(fd2);
        return EXIT_FAILURE;
    }

    write_message(fd3, "fcntl FD: Hello!\n");

    printf("Descriptors: original=%d, dup=%d, dup2=%d, fcntl=%d\n",
           fd, fd1, fd2, fd3);

    close(fd);
    close(fd1);
    close(fd2);
    close(fd3);

    printf("\nFinal file contents:\n");
    display_file();

    return 0;
}


