# shell

A Unix shell implementation written in C, built from scratch. Supports command execution, pipes, and I/O redirection.

## Features

- **Command execution** — run any system command with arguments
- **Pipes** — connect commands with `|`
- **Output redirection** — write output to files with `>` and `>>`
- **Input trimming** — handles leading and trailing whitespace

## Build

```bash
make
```

## Usage

```bash
./shell
```

### Examples

```bash
# Basic command
> ls -la

# Pipe
> ls | grep .c

# Redirect output to file (overwrite)
> echo hello > output.txt

# Redirect output to file (append)
> echo world >> output.txt
```

## Project Structure

```
shell/
├── main.c      — entry point, REPL loop
├── shell.c     — core implementation
├── shell.h     — types, constants, function declarations
└── makefile    — build configuration
```

## Implementation Details

The shell parses each command into a `command_t` struct which tracks arguments, pipe arguments, redirection flags, and file descriptors. Execution forks child processes and uses `execvp` for command execution. Pipes are implemented using `pipe()` and `dup2()` to wire stdout of the first command to stdin of the second.

## Requirements

- GCC
- Linux (uses POSIX APIs — `fork`, `execvp`, `pipe`, `dup2`)
