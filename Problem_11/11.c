/*
 * Problem 11: Duplicating file descriptors and appending
 *
 * Problem statement: Open a file, duplicate its descriptor with dup(), dup2(), and fcntl(), append data through the descriptors, and verify the file contents.
 */

/* Appends four messages through the original descriptor and descriptors made by
 * dup(), dup2(), and fcntl(F_DUPFD).  These duplicates share the open-file state;
 * the helper reopens the file with stdio to print its final contents.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "11.txt"
#define ORIGINALBUFFER "This is written using original fd.\n"
#define DUPBUFFER "This is written using dup fd.\n"
#define DUPBUFFER "This is written using dup2 fd.\n"
#define FCNTLBUFFER "This is written using fcntl fd.\n"

void check_file_update(){
    FILE *file = fopen(FILENAME,"r");
    if(!file){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char ch;
    while ((ch = fgetc(file)) != EOF){
        putchar(ch);
    }
    fclose(file);
}

int main(){
    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    //using original. fd
    if(write(fd, ORIGINALBUFFER, sizeof(ORIGINALBUFFER) - 1) < 0){
        perror("write");
        exit(EXIT_FAILURE);
    }
    
    /************************** */

    //Duplicate fd using dup
    int fd_dup = dup(fd);
    if(fd_dup < 0){
        perror("dup");
        exit(EXIT_FAILURE);
    }

    //write using the duplicated fd
    if(write(fd_dup, DUPBUFFER, sizeof(DUPBUFFER) - 1) < 0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    /*************************** */

    //Duplicate the fd using dup2
    int fd_dup2 = dup2(fd, 10);
    if(fd_dup2 < 0){
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    //duplicated fd from dup2
    if(write(fd_dup2, DUPBUFFER, sizeof(DUPBUFFER) - 1) < 0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    /*************************** */

    //Duplicate the fd using fcntl
    int fd_fcntl = fcntl(fd, F_DUPFD, 0);
    if(fd_fcntl < 0){
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    //duplicated fd from fcntl
    if(write(fd_fcntl, FCNTLBUFFER, sizeof(FCNTLBUFFER) - 1) < 0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    //checking file
    printf("File Contents '%s':\n",FILENAME);
    check_file_update();
    return 0;

}



