# Problem 29: Getting and Modifying Scheduling Policy

## Problem statement
Obtain the current scheduling policy and attempt to modify it using policies such as `SCHED_FIFO` and `SCHED_RR`.

## Key calls
- `sched_getscheduler()`
- `sched_setscheduler()`

## Execution
Compile and run the program. Real-time scheduling policies commonly require appropriate privileges.
