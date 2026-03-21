# holbertonschool-printf

Custom implementation of `printf` for Holberton.

## Supported conversion specifiers

- `%c` character
- `%s` string
- `%%` percent sign
- `%d` / `%i` signed int
- `%b` unsigned int as binary

## Build (library objects)

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format -c *.c
```

## Quick test

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c tests/main.c -o test_printf
./test_printf
```
