#include "main.h"

/**
 * get_func - returns the function for a format specifier
 * @c: the format specifier character
 * @formats: array of format_t structs
 *
 * Return: pointer to the function or NULL
 */
int (*get_func(char c, format_t *formats))(va_list)
{
	int i;

	i = 0;
	while (formats[i].spec != '\0')
	{
		if (formats[i].spec == c)
			return (formats[i].f);
		i++;
	}
	return (NULL);
}

/**
 * handle_percent - handles a percent sequence in the format string
 * @format: the format string
 * @i: index pointer (points to '%', will be advanced)
 * @args: the argument list
 * @formats: array of supported formats
 * @count: printed character count
 *
 * Return: 0 on success, -1 on error
 */
static int handle_percent(const char *format, int *i, va_list args,
		format_t *formats, int *count)
{
	int (*f)(va_list);

	(*i)++;
	if (format[*i] == '\0')
		return (-1);

	f = get_func(format[*i], formats);
	if (f == NULL)
	{
		write(1, "%", 1);
		write(1, &format[*i], 1);
		*count += 2;
	}
	else
		*count += f(args);

	return (0);
}

/**
 * _printf - produces output according to a format
 * @format: the format string
 * @...: the arguments
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i;
	int count;
	format_t formats[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'d', print_int},
		{'i', print_int},
		{'b', print_binary},
		{'\0', NULL}
	};

	if (format == NULL)
		return (-1);

	va_start(args, format);
	i = 0;
	count = 0;

	while (format[i])
	{
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			count++;
		}
		else
		{
			if (handle_percent(format, &i, args, formats, &count) == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		i++;
	}
	va_end(args);
	return (count);
}
