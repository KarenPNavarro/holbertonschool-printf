#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...);
int _putchar(char c);
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_int(va_list args);

/**
 * struct format_s - struct for format specifiers
 * @spec: the format specifier character
 * @f: the function to handle it
 */
typedef struct format_s
{
	char spec;
	int (*f)(va_list);
} format_t;

#endif

