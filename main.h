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
	int (*f)(va_list *);
} format_t;

int _printf(const char *format, ...);
int print_char(va_list *args);
int print_string(va_list *args);
int print_percent(va_list *args);
int print_int(va_list *args);
int print_unsigned(va_list *args);
int print_octal(va_list *args);
int print_hex_lower(va_list *args);
int print_hex_upper(va_list *args);
int print_binary(va_list *args);
int print_S(va_list *args);
int print_pointer(va_list *args);
int print_rev(va_list *args);
int print_rot13(va_list *args);
int (*get_func(char c, format_t *formats))(va_list *);
int print_uint(unsigned long int n);
int print_base(unsigned long int n, int base, int upper);
int print_long(long int n);
int get_precision(const char *format, int *i, va_list *args);
int print_str_prec(char *str, int precision);
int print_uint_prec(unsigned long int n, int precision);
int print_base_prec(unsigned long int n, int base, int upper,
		int precision);
int print_long_prec(long int n, int precision);
int _buf_flush(void);
void _buf_discard(void);
int _buf_putc(char c);
int _buf_write(const char *s, int len);
int get_width(const char *format, int *i, va_list *args);
int handle_format(const char *format, int *i, va_list *args,
		format_t *formats);

#endif
