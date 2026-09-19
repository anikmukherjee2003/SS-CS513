# Problem 22: Creating a Zombie Process

## Problem statement
Create a child process that terminates while its parent delays reaping it, producing a zombie process.

## Key calls
- `fork()`
- `sleep()`
- `wait()` or `waitpid()`

## Execution
Run the program and inspect the process table with `ps` while the child is terminated but not yet reaped.
