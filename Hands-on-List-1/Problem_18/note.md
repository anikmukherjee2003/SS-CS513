# Problem 18: Record Locking

## Problem statement
Create three records in a file. Lock the selected record before reading or modifying it to prevent race conditions. Implement both read and write record locks.

## Key calls
- `fcntl()`
- `F_RDLCK`
- `F_WRLCK`
- `F_UNLCK`

## Execution
Compile and run the program with the selected record index and operation as required by the implementation.
