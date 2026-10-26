# Process Timing with the Timestamp Counter

## Problem statement
Measure and display the processor timestamp-counter interval around a `getpid()` system call.

## Key calls and concepts
- `getpid()`
- Processor timestamp counter via `rdtsc`

## Execution
Compile and run the program on a supported architecture. The result is a processor-cycle interval, not a portable wall-clock duration.
