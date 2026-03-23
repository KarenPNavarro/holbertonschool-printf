#include "main.h"

/**
 * get_width - reads field width from format string
 * @format: format string
 * @i: current index pointer
 * @args: argument list
 *
 * Return: field width
 */
int get_width(const char *format, int *i, va_list *args)
{
	int width;

	width = 0;
	if (format[*i] == '*')
	{
		width = va_arg(*args, int);
		(*i)++;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			width = width * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	return (width);
}
