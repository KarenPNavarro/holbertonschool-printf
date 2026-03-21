#include "main.h"

/**
 * put_hex_byte - prints a byte as two uppercase hex digits
 * @c: byte to print
 */
static void put_hex_byte(unsigned char c)
{
	const char *digits;
	char hi;
	char lo;

	digits = "0123456789ABCDEF";
	hi = digits[(c >> 4) & 0x0F];
	lo = digits[c & 0x0F];
	_buf_putc(hi);
	_buf_putc(lo);
}

/**
 * print_S - prints a string, escaping non printable characters as \xHH
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_S(va_list args)
{
	char *str;
	int i;
	int count;
	unsigned char c;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

	i = 0;
	count = 0;
	while (str[i])
	{
		c = (unsigned char)str[i];
		if ((c > 0 && c < 32) || c >= 127)
		{
			_buf_putc('\\');
			_buf_putc('x');
			put_hex_byte(c);
			count += 4;
		}
		else
		{
			_buf_putc((char)c);
			count++;
		}
		i++;
	}

	return (count);
}
