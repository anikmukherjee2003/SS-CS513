# SS-CS513 Operating Systems Lab

Hands-on C and shell exercises for the SS-CS513 Systems Software and Operating Systems lab. The programs demonstrate Linux system calls, process behavior, file operations, inter-process communication, resource controls, timers, threads, and signals.

## Exercise collections

| Directory | Coverage |
|---|---|
| [`Hands-on-List-1/`](Hands-on-List-1/) | Exercises 1–30: file management, process management, file locking, process scheduling, and daemon processes. Most exercises are in `Problem_N/` folders with a `note.md` and one or more C sources. |
| [`Hands-on-List-2/`](Hands-on-List-2/) | Exercises 31–64: pipes, FIFOs, System V IPC, sockets, timers, resource limits, multithreading, and signals. The source folders are named `P31/` through `P64/`. |

Each collection has its own README. The second list's README includes a detailed exercise index, build examples, and run-order notes. Some exercises have multiple source files because each variant is a separate program.

## Requirements

- Linux (Ubuntu, a Linux virtual machine, or WSL with a working Linux distribution)
- GCC with GNU C support
- `strace` for the FIFO comparison in `Hands-on-List-2/P36/P36c.c`
- POSIX threads for the pthread examples (`-pthread`)

These programs use Linux/POSIX APIs and are not intended to compile natively with Windows MinGW. Compile and run them in Linux.

## Compile and run

Compile each C source as its own program from the relevant exercise directory. For example, from the repository root:

```sh
cd Hands-on-List-1/Problem_3
gcc -std=gnu11 -Wall -Wextra 3.c -o problem3
./problem3
```

For the second collection:

```sh
cd Hands-on-List-2
gcc -std=gnu11 -Wall -Wextra P31/P31.c -o P31/P31
./P31/P31
```

Use `-pthread` when compiling the pthread examples, such as `P52a.c`, `P52b.c`, and `P58.c`:

```sh
gcc -std=gnu11 -Wall -Wextra -pthread P58/P58.c -o P58/P58
```

Run programs from their exercise directory when they use relative paths or sample data files. Check the exercise notes for required arguments, peer programs, and cleanup steps.

## Running the demonstrations

Some programs wait for input, a signal, another process, or a network client. Others intentionally demonstrate deadlock, process termination, or read-only memory. A few create files repeatedly or leave IPC objects for inspection. Follow the run-order and cleanup instructions in the relevant README and `note.md`; use a disposable working directory for exercises that create files.

## Topics

- File descriptors, file metadata, links, pipes, FIFOs, and file locks
- Processes, `fork()`, `exec()`, `waitpid()`, scheduling, and daemons
- System V message queues, shared memory, and semaphores
- TCP sockets and concurrent servers
- Interval timers, resource limits, system limits, and timestamp counters
- POSIX threads and signal handling with `signal()` and `sigaction()`
