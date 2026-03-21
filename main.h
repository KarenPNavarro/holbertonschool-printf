#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

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

int _printf(const char *format, ...);
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_int(va_list args);
int print_binary(va_list args);
int (*get_func(char c, format_t *formats))(va_list);

#endif
