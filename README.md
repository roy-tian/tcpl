# The C Programming Language (K&R) Exercises

This repository contains solutions to exercises from *The C Programming Language* by Kernighan and Ritchie.  Code is organized by chapter, with each directory containing C implementations for that chapter's problems.

## Repository structure

- `c1-tutorial` – fundamentals, input/output, and basic string processing
- `c2-types-operators-expressions` – type systems and bitwise operations
- `c3-control-flows` – loops, conditionals, and other control flow constructs
- `c4-functions` – functions, recursion, and simple utilities
- `c5-pointers` – pointers, arrays, and variable arguments
- `c6-structures` – structures, unions, and related programs
- `c7-io` – file input/output and command-line tools

Each subdirectory contains standalone programs or small utilities that illustrate concepts from the corresponding chapter.

## Building and running

Most programs can be compiled with a C11-compatible compiler such as `gcc`:

```sh
gcc -std=c11 path/to/file.c -o program
./program
```

Some subdirectories may include multiple source files that can be compiled together or with simple makefiles. Refer to comments within each directory for details.

## License

This repository is intended for educational purposes. See individual files for specific license information where provided.
