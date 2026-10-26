# Problem 5: Continuous File Creation

## Problem statement
Create five new files repeatedly in an infinite loop. Run the program in the background and inspect its file descriptor table at `/proc/<pid>/fd`.

## Key concepts
- Repeated file creation
- Open file descriptors
- `/proc/<pid>/fd`

## Execution
Run the program in the background, record its PID, and inspect the symbolic links in `/proc/<pid>/fd`.
