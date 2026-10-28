# Systems Programming Lab — Hands-on List 1

Linux C and shell exercises covering file operations, file locking, process
management, and scheduling. The folders `Problem_1`–`Problem_30` correspond in
order to exercises 1–30 in the assignment.

## Requirements

- Linux (Ubuntu or WSL recommended)
- GCC

These examples use Linux/POSIX APIs and are not intended to compile natively
with Windows MinGW.

## Build and run

Run commands from this directory. For example:

```sh
gcc -std=gnu11 -Wall -Wextra Problem_3/3.c -o Problem_3/3
./Problem_3/3
```

Build every C source into a separate mirrored `build/` directory:

```sh
while IFS= read -r source; do
    output="build/${source%.c}"
    mkdir -p "$(dirname "$output")"
    gcc -std=gnu11 -Wall -Wextra "$source" -o "$output" || exit 1
done < <(find P* -type f -name '*.c' | sort)
```

Each C source is a separate program or variant; compile the exercise entry
point you intend to run. Problem 1 also has a shell implementation at
`Problem_1/Shell/1_shell.sh`. Run programs from their exercise directory when
they use relative paths or supplied sample files, and check the matching
`note.md` for arguments and execution details.

## Exercise index

### I. File operations and locking

| Exercise | Source file(s) | Topic |
|---|---|---|
| 1 | `Problem_1/1a.c`–`1c.c`; `Problem_1/Shell/1_shell.sh` | Create symbolic links, hard links, and a FIFO using system calls and shell commands. |
| 2 | `Problem_2/2.c` | Run a background process that traverses `/proc` and reports process information. |
| 3 | `Problem_3/3.c` | Create a file with `creat()` and print its file descriptor. |
| 4 | `Problem_4/4.c` | Open an existing file using `open()` and examine the result. |
| 5 | `Problem_5/5.c` | Repeatedly create files and inspect the process's open file descriptors. |
| 6 | `Problem_6/6.c` | Read standard input and write standard output using `read()` and `write()`. |
| 7 | `Problem_7/7.c` | Copy a file using `open()`, `read()`, and `write()`. |
| 8 | `Problem_8/8.c` | Open a file read-only, display its contents, and close it at EOF. |
| 9 | `Problem_9/9.c` | Display file metadata and access, modification, and change times. |
| 10 | `Problem_10/10.c` | Write data around a seek-created gap using `lseek()`. |
| 11 | `Problem_11/11.c` | Duplicate file descriptors with `dup()`, `dup2()`, and `fcntl()`, then append data. |
| 12 | `Problem_12/12.c` | Determine a file's opening access mode using `fcntl()`. |
| 13 | `Problem_13/13.c` | Wait up to 10 seconds for standard input using `select()`. |
| 14 | `Problem_14/14.c` | Identify a path's file type using file metadata. |
| 15 | `Problem_15/15.c` | Display environment variables using `environ`. |
| 16 | `Problem_16/16a.c`, `16B.c`, `advisorywirte.c` | Demonstrate advisory and mandatory file locking with read and write locks. |
| 17 | `Problem_17/17A.c`, `17B.c` | Serialize ticket-number updates with a file write lock. |
| 18 | `Problem_18/18.c` | Lock selected records for reading or modification. |

### II. Processes, execution, and scheduling

| Exercise | Source file(s) | Topic |
|---|---|---|
| 19 | `Problem_19/19.c` | Measure the processor timestamp-counter interval around `getpid()`. |
| 20 | `Problem_20/20.c` | Create a process with `fork()` and print parent/child process IDs. |
| 21 | `Problem_21/21.c` | Have parent and child processes write to a file. |
| 22 | `Problem_22/22.c` | Create a zombie by delaying the parent's reaping of a terminated child. |
| 23 | `Problem_23/23.c` | Create an orphan process and observe its reparenting. |
| 24 | `Problem_24/24.c` | Create three children and wait for a selected child with `waitpid()`. |
| 25 | `Problem_25/25.c` | Execute another program and pass it a command-line argument. |
| 26 | `Problem_26/26.c`, `a.out.c` | Execute `ls -Rl` using the `execl*()` and `execv*()` variants. |
| 27 | `Problem_27/execl.c`, `execlp.c`, `execle.c`, `execv.c`, `execvp.c` | Demonstrate the `exec` family of functions. |
| 28 | `Problem_28/28.c` | Read and modify process priority using the `nice` mechanism. |
| 29 | `Problem_29/29.c` | Read and attempt to change the process scheduling policy. |
| 30 | `Problem_30/30.c` | Create a daemon that runs a task at a specified time or interval. |

## Run order and behavior notes

- Problems 2 and 5 run indefinitely; start them in the background, inspect
  their `/proc/<pid>` information, and stop them when finished.
- Problem 13 waits up to 10 seconds for input.
- For Problem 16, run the read-lock and write-lock examples against the
  supplied test files; test the lock behavior from another process.
- For Problem 17, run the initializer once before starting one or more ticket
  reservation processes.
- Problem 18 demonstrates record locking; coordinate separate processes when
  testing lock contention.
- Problem 21 has concurrent parent and child writes, so output order can vary.
- Problem 22 deliberately leaves a terminated child unreaped briefly so it
  can be observed as a zombie. Problem 23 lets the parent exit before its
  child.
- Problem 28 may require privileges to decrease the process niceness.
  Real-time scheduling changes in Problem 29 commonly require privileges.
- Problem 30 detaches into a daemon; note its PID and stop it after testing.
- Some exercises create or modify files. Use the supplied sample files where
  appropriate, inspect each `note.md`, and use a disposable working directory
  when experimenting.
