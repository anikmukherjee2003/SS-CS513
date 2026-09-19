# Problem 16: Mandatory Locking

## Problem statement
Implement mandatory file locking with both a write lock and a read lock.

## Key concepts
- File permission configuration for mandatory locking
- `fcntl()` record locks
- `F_WRLCK` and `F_RDLCK`

## Execution
Compile and run the write-lock and read-lock programs against the supplied test files. Test access from another process while a lock is held.
