# Problem 17: Online Ticket Reservation

## Problem statement
Initialize a ticket number in one program. In a separate program, acquire a write lock, read and increment the ticket number, print the new number, and close the file.

## Key calls
- `open()`
- `read()` and `write()`
- `fcntl()` with `F_WRLCK`

## Execution
Run the initializer once, then start multiple reservation processes to verify serialized ticket allocation.
