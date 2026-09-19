# Demonstrates shell equivalents of the Problem_1 filesystem calls: ln -s creates a
# symbolic link, ln creates a hard link, and mkfifo creates a named pipe.
# The commands operate on the names in the current working directory.
# Name: Aayank Singhai (MT2025001)

# 1.a Soft link (symlink system call)
ln -s source.txt softLink.txt

# 1.b Hard link (link system call) 
ln source.txt hardLink.txt

# 1.c FIFO (mkfifo Library Function or mknod system call)
mkfifo fifo


#OUTPUT
#anikm@ANIK:~/Hands-On-List1-Files/Problem_1/Shell$ sh 1_shell.sh
#anikm@ANIK:~/Hands-On-List1-Files/Problem_1/Shell$ ls
#1_shell.sh  fifo  hardLink.txt  softLink.txt  source.txt