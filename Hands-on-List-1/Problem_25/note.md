# Problem 25: Executing an Executable Program

## Problem statement
Execute another program using an `exec` system call and pass input to it as a command-line argument, for example `./a.out name`.

## Key call
- An `exec` family function such as `execvp()`

## Execution
Compile the target executable first, then compile and run the caller from the directory containing it.
