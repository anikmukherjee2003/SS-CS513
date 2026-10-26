# Problem 10: File Write and Seek

## Problem statement
Write 10 bytes, move the file pointer forward by 10 bytes with `lseek()`, and write another 10 bytes. Check the return value and inspect the empty space with `od`.

## Key calls
- `write()`
- `lseek()`

## Execution
Compile and run the program, then use `od -c` or `od -x` on the generated file to inspect the hole between the writes.
