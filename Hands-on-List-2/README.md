# Systems Programming Lab — Hands-on List 2

Linux C exercises for System V IPC, timers, resource limits, threads, and
signals. The folders `P31`–`P64` correspond in order to exercises 1–34 in the
assignment: `P31` is exercise 1, and `P64` is exercise 34.

## Requirements

- Linux (Ubuntu or WSL recommended)
- GCC
- `strace` for the FIFO comparison in P36c

These examples use Linux/POSIX APIs and are not intended to compile natively
with Windows MinGW.

## Build and run

Run commands from this directory. For example:

```sh
gcc -std=gnu11 -Wall -Wextra -pthread P31/P31.c -o /tmp/P31
/tmp/P31
```

Build every C entry point into a local `build/` directory:

```sh
mkdir -p build
while IFS= read -r source; do
    output="build/$(basename "${source%.c}")"
    gcc -std=gnu11 -Wall -Wextra -pthread "$source" -o "$output" || exit 1
done < <(find P* -type f -name '*.c' | sort)
```

Each lettered source file is a separate program. Shared headers such as
`pipeline.h` and `common.h` contain implementations used by that exercise's
entry points; compile the `.c` entry point, not the header. Some programs wait
for input, signals, network clients, or IPC peers, so they may not exit
immediately.

## Exercise index

### III. System V IPC mechanisms

| Exercise | Source file(s) | Topic |
|---|---|---|
| 1 | `P31/P31.c` | Create a pipe, write to it, read from it, and display the data. |
| 2 | `P32/P32.c` | Send data from a parent process to its child. |
| 3 | `P33/P33.c` | Two-way communication between parent and child. |
| 4 | `P34/P34a.c`–`P34c.c` | Implement `ls -l \| wc` using `dup`, `dup2`, and `fcntl`. |
| 5 | `P35/P35.c` | Count current-directory entries that are directories using `ls -l \| grep ^d \| wc` and `dup2`. |
| 6 | `P36/P36a.c`–`P36e.c` | FIFO creation: `P36a` runs `mknod`, `P36b` runs `mkfifo`, `P36c` compares them with `strace`, `P36d` calls `mknod()`, and `P36e` calls `mkfifo()`. |
| 7 | `P37/P37a.c`, `P37b.c` | One-way FIFO communication. |
| 8 | `P38/P38a.c`, `P38b.c` | Two-way FIFO communication. |
| 9 | `P39/P39.c` | Wait up to 10 seconds for FIFO data using `select()`. |
| 10 | `P40/P40.c` | Print the process file limit and pipe capacity. |
| 11 | `P41/P41.c` | Create/find a message queue and print its key and ID. |
| 12 | `P42/P42a.c`–`P42h.c` | Inspect queue access mode (`a`), UID/GID (`b`), send/receive times (`c`), change time (`d`), current bytes (`e`), message count (`f`), byte limit (`g`), and sender/receiver PIDs (`h`). |
| 13 | `P43/P43.c` | Send a message to a message queue. |
| 14 | `P44/P44a.c`, `P44b.c` | Receive from a queue with blocking flags `0` or nonblocking `IPC_NOWAIT`. |
| 15 | `P45/P45.c` | Change message-queue permissions. |
| 16 | `P46/P46.c` | Remove a message queue. |
| 17 | `P47/P47a.c`–`P47d.c` | Create/write shared memory, test a read-only attachment, detach, and remove the segment. |
| 18 | `P48/P48a.c`, `P48b.c` | Create and initialize binary and counting semaphores. |
| 19 | `P49/P49a.c`–`P49d.c` | Semaphore-protected ticket creation (`a`), shared-memory writes (`b`), counting pseudo-resources (`c`), and semaphore removal (`d`). |
| 20 | `P50/P50.c` | Demonstrate a semaphore deadlock. |
| 21 | `P51/P51a.c`, `P51b.c` | Communicate between machines with a TCP socket. |
| 22 | `P52/P52a.c`, `P52b.c` | Concurrent TCP servers using `fork()` and `pthread_create()`. |

### IV. Timers, resource limits, multithreading, and signals

| Exercise | Source file(s) | Topic |
|---|---|---|
| 23 | `P53/P53a.c`–`P53c.c` | Ten-second initial interval timers: `ITIMER_REAL` (`a`), `ITIMER_VIRTUAL` (`b`), and `ITIMER_PROF` (`c`), each with a 10-microsecond repeat interval. |
| 24 | `P54/P54.c` | Print resource limits with `getrlimit()`. |
| 25 | `P55/P55.c` | Set a resource limit with `setrlimit()`. |
| 26 | `P56/P56.c` | Measure 100 `getppid()` calls with the timestamp counter. |
| 27 | `P57/P57a.c`–`P57g.c` | Query exec argument bytes (`a`), per-UID processes (`b`), clock ticks (`c`), open files (`d`), page size (`e`), physical pages (`f`), and available pages (`g`). |
| 28 | `P58/P58.c` | Create three threads and print their IDs. |
| 29 | `P59/P59a.c`–`P59g.c` | Catch `SIGSEGV` (`a`), `SIGINT` (`b`), `SIGFPE` (`c`), `SIGALRM` via `alarm()` (`d`) and `setitimer()` (`e`), `SIGVTALRM` (`f`), and `SIGPROF` (`g`) using `signal()`. |
| 30 | `P60/P60.c` | Ignore `SIGINT`, then restore its default action using `signal()`. |
| 31 | `P61/P61a.c`–`P61c.c` | Catch `SIGSEGV` (`a`), `SIGINT` (`b`), and `SIGFPE` (`c`) using `sigaction()`. |
| 32 | `P62/P62.c` | Ignore `SIGINT`, then restore its default action using `sigaction()`. |
| 33 | `P63/P63.c` | Create an orphan by having the child send `SIGKILL` to its parent. |
| 34 | `P64/P64a.c`, `P64b.c` | Demonstrate that `SIGSTOP` cannot be caught; send it with `kill()`. |

## Run order and behavior notes

- FIFO examples: start `P37b` before `P37a`; start `P38a` before `P38b`.
- Message queues: run `P41`, then `P43` to send and `P44a` or `P44b` to
  receive. `P44a` blocks while the queue is empty; `P44b` returns immediately.
  Use `P45` to change permissions and `P46` to remove the queue. Check queue
  state with `ipcs -q`.
- Shared memory: run `P47a` before `P47b` or `P47c`; run `P47d` to remove the
  segment.
- `P48a` and `P48b` leave semaphore sets available for inspection and print
  their IDs. Remove a set with `ipcrm -s ID` when finished.
- `P50` deliberately creates a brief deadlock, then removes the semaphore set
  to release its children.
- `P51a` listens on port 5051 by default; run `P51b SERVER_HOST` on the other
  machine. Ensure the network permits TCP port 5051.
- `P52a` and `P52b` are long-running servers. They accept an optional port
  argument and default to port 5052; stop them with Ctrl-C.
- P36c requires `strace`. The P53 timers wait for a first expiry after 10
  seconds; the 10-microsecond value is the repeating interval.
- The SIGINT examples wait for Ctrl-C. `P47b` deliberately faults a child
  process when it tries to write to a read-only shared-memory mapping;
  `P59a` and `P61a` trigger `SIGSEGV` in their own process.
- `P63` intentionally kills its parent process. Start `P64a`, note its PID,
  then pass that PID to `P64b`; the second program sends `SIGSTOP` and then
  `SIGCONT` so the first process can report the result.

## Compilation check

All 76 C source files compiled successfully with GCC on Ubuntu/WSL using
`-std=gnu11 -Wall -Wextra -pthread`. This confirms the entry points compile;
interactive and multi-process behavior should still be exercised on Linux
following the run-order notes above.
