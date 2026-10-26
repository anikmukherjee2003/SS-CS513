# Problem 30: Running a Script at a Specific Time with a Daemon

## Problem statement
Create a daemon process that detaches from the terminal and executes a task at a specified time or interval.

## Key calls
- `fork()`
- `setsid()`
- `chdir()`
- `umask()`

## Execution
Run the program in the background and inspect its output or log. Stop the daemon using its PID when testing is complete.
