*This project has been created as part of the 42 curriculum by smaragat.*

# get_next_line

## Description

`get_next_line` is a 42 school project whose goal is to implement a function
that reads and returns one line at a time from a file descriptor. A line ends
at the newline character (`\n`), and the newline is included in the returned
string when it is present.

The project demonstrates low-level file reading with the POSIX `read` system
call, dynamic memory allocation, string manipulation, and the use of static
storage between function calls. The buffer size is configurable at compile
time through `BUFFER_SIZE`.

The repository currently contains:

- `get_next_line.c`: the main reading and line-extraction logic.
- `get_next_line_utils.c`: helper functions for strings and stored data.
- `get_next_line.h`: public declarations and configuration macros.

## Instructions

### Requirements

- A C compiler such as `cc` or `clang`.
- POSIX-compatible system calls, including `read`, `open`, and `close`.

### Compilation

From the project root, compile the implementation together with the example
program:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c main.c -o get_next_line
```

`BUFFER_SIZE` can be changed to test different read sizes:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
    get_next_line.c get_next_line_utils.c main.c -o get_next_line
```

### Execution

Run the generated executable from the project root:

```sh
./get_next_line
```

The example opens `some_file.txt`, repeatedly calls `get_next_line`, prints
each returned line, frees it, and closes the file descriptor.

### API

```c
char *get_next_line(int fd);
```

The function returns a newly allocated line on success. It returns `NULL` when
there is no more data to read or when an invalid file descriptor or allocation
failure is encountered. The caller is responsible for freeing every returned
line.

## Algorithm

The implementation uses a persistent string called `stored`. It is declared
as `static` inside `get_next_line`, so its content survives after the function
returns and is available during the next call.

For each call, the algorithm follows these steps:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Allocate a temporary buffer with `BUFFER_SIZE + 1` bytes.
3. Read chunks with `read` until `stored` contains a newline or end-of-file is
   reached.
4. Append each chunk to `stored`.
5. Find the first newline and copy the corresponding line into a new string.
6. Remove the returned line from `stored`, including its newline, while keeping
   all remaining characters for the next call.
7. Return the allocated line to the caller.

The persistent storage is necessary because one call to `read` can return more
than one line. For example, a single read may produce:

```text
first line
second line
```

The first call returns `first line\n` and keeps `second line\n` in `stored`.
The next call can then return the second line without reading the same bytes
again.

### Algorithm justification

Reading in chunks avoids making one system call for every character and allows
the function to work with any positive `BUFFER_SIZE`. Searching for a newline
after each chunk ensures that the function stops as soon as a complete line is
available, while the persistent string preserves data that belongs to later
lines.

For a total of `n` characters accumulated for a call, line search and copying
are linear operations, but the current implementation repeatedly reallocates
and copies `stored` when joining chunks. Therefore, its worst-case time cost is
`O(n^2)` for a line of `n` characters. The temporary buffer uses
`O(BUFFER_SIZE)` memory, while `stored` and the returned line use memory
proportional to the data that has been read and retained. A future
implementation could reduce the repeated copying by collecting chunks before
performing a final join.

## Resources

- 42 Project subject: `get_next_line`.
- POSIX `read`: <https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html>
- POSIX `open`: <https://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html>
- POSIX `close`: <https://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html>
- C dynamic memory allocation (`malloc` and `free`): <https://en.cppreference.com/w/c/memory>
- C strings and null-terminated character arrays: <https://en.cppreference.com/w/c/string/byte>

### Use of AI

AI was used as a programming support tool during this project. It helped with:

- reviewing the control flow of `get_next_line`;
- identifying memory-management and error-handling issues;
- reviewing this README for completeness against the project requirements.

The implementation, project decisions, testing, and final verification remain
the responsibility of the project author, `smaragat`.

## Limitations and future improvements

The current example is intended for the mandatory single-file-descriptor use
case. Supporting multiple file descriptors simultaneously would require one
persistent storage pointer per descriptor, as commonly implemented with a
static array indexed by `fd`. A project `Makefile` and a dedicated test suite
could also be added to automate compilation and edge-case testing.
