# Problem 11: File Descriptor Duplication and Appending

## Problem statement
Open a file, duplicate its descriptor with `dup()`, `dup2()`, and `fcntl()`, append data through the descriptors, and verify the file contents.

## Key calls
- `dup()`
- `dup2()`
- `fcntl(F_DUPFD)`

## Execution
Compile and run the program, then inspect the output file.
