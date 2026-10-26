# Problem 21: File Writing by Parent and Child Processes

## Problem statement
Open a file, call `fork()`, allow both the child and parent to write to the file, and examine the resulting output.

## Key calls
- `open()`
- `fork()`
- `write()`

## Execution
Compile and run the program, then inspect the generated file. Output ordering can vary because the processes execute concurrently.
