/*
 * Problem 4: Opening an existing file with O_EXCL
 *
 * Problem statement: Open an existing file in read-write mode and experiment with the O_EXCL flag to observe exclusive-open behavior.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    /* File we want to open */
    const char *file_path = "anik4.txt";

    /* open(file, flags, mode)
     * O_RDWR -> open for reading and writing
     * O_EXCL -> fail if the file already exists (without O_CREAT, this usually
     *           means the file must be absent, so open() fails)
     */
    int fd = open(file_path, O_RDWR | O_EXCL, 0644);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("Successfully opened file with Read and Write mode\n");
    printf("File Descriptor Value: %d\n", fd);
    return 0;
}


/*OUTPUT:
//Without anik4.txt
anikm@ANIK:~/Hands-On-List1-Files/Problem_4$ ./4
Error opening file
: No such file or directory

//With anik4.txt
anikm@ANIK:~/Hands-On-List1-Files/Problem_4$ ./4
Successfully opened file with Read and Write mode
File Descriptor Value: 3
*/