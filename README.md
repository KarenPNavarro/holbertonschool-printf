# holbertonschool-printf

Custom implementation of `printf` for Holberton.

## Supported conversion specifiers

- `%c` character
- `%s` string
- `%%` percent sign
- `%d` / `%i` signed int
- `%b` unsigned int as binary
- `%u` unsigned int
- `%o` unsigned int as octal
- `%x` unsigned int as hexadecimal (lowercase)
- `%X` unsigned int as hexadecimal (uppercase)
- `%S` string with non printable chars as `\\xHH`

## Build (library objects)

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format -c *.c
```

## Quick test

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c tests/main.c -o test_printf
./test_printf
```
