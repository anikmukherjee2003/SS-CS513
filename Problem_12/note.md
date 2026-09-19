# Problem 12: Determining the Opening Mode of a File

## Problem statement
Use `fcntl()` to determine the access mode with which a file was opened.

## Key call
- `fcntl(F_GETFL)`

## Execution
Compile and run the program, then compare the reported flags with read-only, write-only, and read-write modes.
