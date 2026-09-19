/*
 * Problem 5: Continuous file creation and descriptor inspection
 *
 * Problem statement: Create five new files repeatedly in an infinite loop, run the program in the background, and inspect its descriptors under /proc/<pid>/fd.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    /* Infinite loop: keeps creating/opening files repeatedly */
    while (1) {
        /* Create/open five files in sequence */
        for (int i = 1; i <= 5; ++i) {
            char filename[10];
            snprintf(filename, sizeof(filename), "file%d", i);

            /* open() returns a file descriptor. O_CREAT creates the file if it
             * does not already exist, and O_WRONLY opens it for writing.
             */
            int fd = open(filename, O_CREAT | O_WRONLY, 0644);
            if (fd < 0) {
                perror("error in opening the file");
                return 1;
            }

            /* Keep the file open for a short time so we can inspect it in /proc */
            sleep(10);

            /* Close the descriptor when done */
            close(fd);
        }
    }

    return 0;
}

/*OUTPUT:
anikm@ANIK:~/Hands-On-List1-Files/Problem_5$ ps -ef | grep ./5
root         196       1  0 Sep18 ?        00:00:00 snapfuse /var/lib/snapd/snaps/tree_54.snap /snap/tre/54 -o ro,nodev,allow_other,suid
anikm      42404   42397  0 06:44 pts/5    00:00:00 -bash
anikm      56512   42404  0 07:31 pts/5    00:00:00 ./5
anikm      56579   55471  0 07:31 pts/0    00:00:00 grep --color=auto ./5
anikm@ANIK:~/Hands-On-List1-Files/Problem_5$ ls -l /proc/56512/fd
total 0
lrwx------ 1 anikm anikm 64 Sep 19 07:32 0 -> /dev/pts/5
lrwx------ 1 anikm anikm 64 Sep 19 07:32 1 -> /dev/pts/5
lrwx------ 1 anikm anikm 64 Sep 19 07:32 2 -> /dev/pts/5
l-wx------ 1 anikm anikm 64 Sep 19 07:32 3 -> /home/anikm/Hands-On-List1-Files/Problem_5/file5
*/