# Problem 23: Creating an Orphan Process

## Problem statement
Create an orphan process by allowing the parent to exit before the child, then observe the child's reparenting.

## Key calls
- `fork()`
- `sleep()`
- `getppid()`

## Execution
Run the program and observe the child's parent PID before and after the original parent exits.
