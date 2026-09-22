
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("1.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd == -1) {
        perror("Error opening 1.txt");
        exit(EXIT_FAILURE);
    }

    int fd1 = dup2(fd, STDOUT_FILENO);

    if (fd1 == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Hello\n");
    fflush(stdout);

    close(fd);
    close(STDOUT_FILENO);

    return 0;
}