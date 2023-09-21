##LIBASM

### Project Description

This project, called `libasm`, is an attempt to recreate some commonly used C standard library functions, but written in x86_64 Intel Assembly. It serves as a foundational exercise to better understand low-level operations in a Unix environment. The library, compiled into `libasm.a`, includes rewritten versions of `ft_strlen`, `ft_strcpy`, `ft_strcmp`, `ft_write`, `ft_read`, and `ft_strdup`.

#### Implemented Functions:

1. **ft_strlen**: Calculates the length of a string.
2. **ft_strcpy**: Copies a string from source to destination.
3. **ft_strcmp**: Compares two strings.
4. **ft_write**: Writes data to a file descriptor.
5. **ft_read**: Reads data from a file descriptor.
6. **ft_strdup**: Duplicates a string using malloc.

#### Error Handling:

- The project takes care of syscall errors and sets the `errno` variable properly as required.
- We are allowed to call extern `___error` or `errno_location` to manage `errno`.

#### Testing:

The project includes a `test.c` that tests these functions to ensure that they are working as expected. This `main.c` is compiled alongside `libasm.a` to demonstrate the functionality.
