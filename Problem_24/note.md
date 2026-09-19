# Problem 24: Creating and Waiting for Child Processes

## Problem statement
Create three child processes and have the parent wait for a specific child using `waitpid()`.

## Key calls
- `fork()`
- `waitpid()`

## Execution
Compile and run the program. Verify that the parent waits for the requested child and reports its termination status.
