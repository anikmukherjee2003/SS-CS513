# Problem 14: File Type Identification

## Problem statement
Take a path from the command line and identify whether it is a regular file, directory, symbolic link, FIFO, device, or another supported file type.

## Key calls
- `lstat()` or `stat()`
- File-type macros such as `S_ISREG()` and `S_ISDIR()`

## Execution
Compile the program and pass different filesystem paths as arguments.
