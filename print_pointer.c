#include <stdint.h>
#include "main.h"

/**
 * print_pointer - prints a pointer address
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_pointer(va_list *args)
{
	void *ptr;
	uintptr_t value;
	char buf[sizeof(uintptr_t) * 2];
	const char *digits;
	int len;
	int i;

	ptr = va_arg(*args, void *);
	if (ptr == NULL)
	{
		_buf_write("(nil)", 5);
		return (5);
	}

	digits = "0123456789abcdef";
	value = (uintptr_t)ptr;
	len = 0;
	while (value > 0)
	{
		buf[len] = digits[value % 16];
		len++;
		value /= 16;
	}

	_buf_putc('0');
	_buf_putc('x');
	i = len - 1;
	while (i >= 0)
	{
		_buf_putc(buf[i]);
		i--;
	}

	return (len + 2);
}
