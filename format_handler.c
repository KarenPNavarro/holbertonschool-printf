#include <stdint.h>
#include "main.h"

/**
 * parse_flags - parses +, space, #, 0 and - flags
 * @format: format string
 * @i: current index pointer
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 * @zero: '0' flag
 * @minus: '-' flag
 */
static void parse_flags(const char *format, int *i, int *plus, int *space,
		int *hash, int *zero, int *minus)
{
	while (format[*i] == '+' || format[*i] == ' ' || format[*i] == '#' ||
			format[*i] == '0' || format[*i] == '-')
	{
		if (format[*i] == '+')
			*plus = 1;
		else if (format[*i] == ' ')
			*space = 1;
		else if (format[*i] == '#')
			*hash = 1;
		else if (format[*i] == '0')
			*zero = 1;
		else
			*minus = 1;
		(*i)++;
	}
}

/**
 * ulen_base - returns digit length of an unsigned number in a base
 * @n: number
 * @base: base
 *
 * Return: number of digits
 */
static int ulen_base(unsigned long int n, unsigned int base)
{
	int len;

	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	return (len);
}

/**
 * repeat_char - writes a repeated character
 * @c: character
 * @n: repeat count
 *
 * Return: number of characters written
 */
static int repeat_char(char c, int n)
{
	int count;

	count = 0;
	while (n > 0)
	{
		_buf_putc(c);
		count++;
		n--;
	}
	return (count);
}

/**
 * print_unknown - prints '%' followed by consumed chars up to the specifier
 * @format: format string
 * @start: index of first char after '%'
 * @end: index of specifier
 *
 * Return: number of characters printed
 */
static int print_unknown(const char *format, int start, int end)
{
	int count;
	int j;

	count = 0;
	_buf_putc('%');
	count++;
	j = start;
	while (j <= end)
	{
		_buf_putc(format[j]);
		count++;
		j++;
	}
	return (count);
}

/**
 * handle_format - handles a percent conversion in the format string
 * @format: the format string
 * @i: index pointer (points to '%', advanced to specifier)
 * @args: the argument list
 * @formats: array of supported formats
 *
 * Return: number of characters printed, or -1 on error
 */
int handle_format(const char *format, int *i, va_list *args, format_t *formats)
{
	int plus, space, hash, zero, minus;
	int width, precision;
	char length;
	int start;
	char spec;
	int pad_len;
	char pad;
	int printed;
	unsigned long int un;
	unsigned long int mag;
	long int sn;
	char sign;
	int digits;
	int prefix_len;
	int (*f)(va_list *);

	start = *i + 1;
	(*i)++;
	if (format[*i] == '\0')
		return (-1);

	plus = 0;
	space = 0;
	hash = 0;
	zero = 0;
	minus = 0;
	parse_flags(format, i, &plus, &space, &hash, &zero, &minus);
	width = get_width(format, i, args);
	precision = get_precision(format, i, args);
	length = 0;
	if (format[*i] == 'l' || format[*i] == 'h')
	{
		length = format[*i];
		(*i)++;
	}
	if (format[*i] == '\0')
		return (-1);

	spec = format[*i];
	pad = (zero && !minus && precision < 0 && (spec == 'd' || spec == 'i' ||
					spec == 'o' || spec == 'x' || spec == 'X' || spec == 'p'))
		? '0' : ' ';
	printed = 0;

	if (spec == 'c')
	{
		pad_len = (width > 1) ? (width - 1) : 0;
		if (!minus)
			repeat_char(' ', pad_len);
		printed = print_char(args);
		if (minus)
			repeat_char(' ', pad_len);
		return (printed + pad_len);
	}
	if (spec == '%')
	{
		pad_len = (width > 1) ? (width - 1) : 0;
		if (!minus)
			repeat_char(' ', pad_len);
		printed = print_percent(args);
		if (minus)
			repeat_char(' ', pad_len);
		return (printed + pad_len);
	}
	if (spec == 's')
	{
		int slen;

		slen = 0;
		if (precision < 0)
			precision = 2147483647;
		{
			char *s;
			int k;

			s = va_arg(*args, char *);
			if (s == NULL)
				s = "(null)";
			k = 0;
			while (s[k] && k < precision)
				k++;
			slen = k;
			pad_len = (width > slen) ? (width - slen) : 0;
			if (!minus)
				repeat_char(' ', pad_len);
			printed = print_str_prec(s, slen);
			if (minus)
				repeat_char(' ', pad_len);
			return ((width > slen) ? width : slen);
		}
	}

	if (spec == 'd' || spec == 'i')
	{
		if (length == 'l')
			sn = va_arg(*args, long int);
		else if (length == 'h')
			sn = (short int)va_arg(*args, int);
		else
			sn = (long int)va_arg(*args, int);

		sign = 0;
		if (sn < 0)
		{
			sign = '-';
			mag = (unsigned long int)(-(sn + 1)) + 1;
		}
		else
		{
			mag = (unsigned long int)sn;
			if (plus)
				sign = '+';
			else if (space)
				sign = ' ';
		}

		digits = (precision == 0 && mag == 0) ? 0 : ulen_base(mag, 10);
		printed = (precision < 0) ? digits : (precision > digits ? precision : digits);
		prefix_len = (sign != 0) ? 1 : 0;
		pad_len = (width > (prefix_len + printed)) ?
			(width - (prefix_len + printed)) : 0;

		if (!minus)
		{
			if (pad == ' ')
				repeat_char(' ', pad_len);
			if (sign)
				_buf_putc(sign);
			if (pad == '0')
				repeat_char('0', pad_len);
			else if (precision > digits)
				repeat_char('0', precision - digits);
			if (!(precision == 0 && mag == 0))
				print_uint(mag);
		}
		else
		{
			if (sign)
				_buf_putc(sign);
			if (precision > digits)
				repeat_char('0', precision - digits);
			if (!(precision == 0 && mag == 0))
				print_uint(mag);
			repeat_char(' ', pad_len);
		}
		return ((width > (prefix_len + printed)) ? width : (prefix_len + printed));
	}

	if (spec == 'u' || spec == 'o' || spec == 'x' || spec == 'X')
	{
		int base;
		int upper;
		int pfx;

		if (length == 'l')
			un = va_arg(*args, unsigned long int);
		else if (length == 'h')
			un = (unsigned short int)va_arg(*args, unsigned int);
		else
			un = (unsigned long int)va_arg(*args, unsigned int);

		base = (spec == 'o') ? 8 : (spec == 'u' ? 10 : 16);
		upper = (spec == 'X');
		pfx = 0;
		if (spec == 'o')
		{
			if (hash && un == 0 && precision == 0)
			{
				printed = 0;
				pad_len = (width > 1) ? (width - 1) : 0;
				if (!minus)
					repeat_char(' ', pad_len);
				_buf_putc('0');
				if (minus)
					repeat_char(' ', pad_len);
				return ((width > 1) ? width : 1);
			}
			digits = (precision == 0 && un == 0) ? 0 : ulen_base(un, base);
			printed = (precision < 0) ? digits : (precision > digits ? precision : digits);
			if (hash && un != 0 && (precision < 0 || precision <= digits))
				pfx = 1;
		}
		else if (spec == 'x' || spec == 'X')
		{
			digits = (precision == 0 && un == 0) ? 0 : ulen_base(un, base);
			printed = (precision < 0) ? digits : (precision > digits ? precision : digits);
			if (hash && un != 0)
				pfx = 2;
		}
		else
		{
			digits = (precision == 0 && un == 0) ? 0 : ulen_base(un, base);
			printed = (precision < 0) ? digits : (precision > digits ? precision : digits);
		}

		pad_len = (width > (pfx + printed)) ? (width - (pfx + printed)) : 0;
		if (!minus)
		{
			if (pad == ' ')
				repeat_char(' ', pad_len);
			if (pfx == 1)
				_buf_putc('0');
			else if (pfx == 2)
			{
				_buf_putc('0');
				_buf_putc(upper ? 'X' : 'x');
			}
			if (pad == '0')
				repeat_char('0', pad_len);
			else if (precision > digits)
				repeat_char('0', precision - digits);
		}
		else
		{
			if (pfx == 1)
				_buf_putc('0');
			else if (pfx == 2)
			{
				_buf_putc('0');
				_buf_putc(upper ? 'X' : 'x');
			}
			if (precision > digits)
				repeat_char('0', precision - digits);
		}

		if (!(precision == 0 && un == 0))
		{
			if (spec == 'u')
				print_uint(un);
			else
				print_base(un, base, upper);
		}
		if (minus)
			repeat_char(' ', pad_len);
		return ((width > (pfx + printed)) ? width : (pfx + printed));
	}

	if (spec == 'p')
	{
		void *ptr;
		uintptr_t value;

		ptr = va_arg(*args, void *);
		if (ptr == NULL)
		{
			int len;

			len = 5;
			pad_len = (width > len) ? (width - len) : 0;
			if (!minus)
				repeat_char(' ', pad_len);
			_buf_write("(nil)", 5);
			if (minus)
				repeat_char(' ', pad_len);
			return ((width > len) ? width : len);
		}

		value = (uintptr_t)ptr;
		digits = (precision == 0 && value == 0) ? 0 : ulen_base(value, 16);
		printed = (precision < 0) ? digits : (precision > digits ? precision : digits);
		prefix_len = 2;
		pad_len = (width > (prefix_len + printed)) ?
			(width - (prefix_len + printed)) : 0;

		if (!minus)
		{
			if (pad == ' ')
				repeat_char(' ', pad_len);
			_buf_write("0x", 2);
			if (pad == '0')
				repeat_char('0', pad_len);
			else if (precision > digits)
				repeat_char('0', precision - digits);
			if (!(precision == 0 && value == 0))
				print_base((unsigned long int)value, 16, 0);
		}
		else
		{
			_buf_write("0x", 2);
			if (precision > digits)
				repeat_char('0', precision - digits);
			if (!(precision == 0 && value == 0))
				print_base((unsigned long int)value, 16, 0);
			repeat_char(' ', pad_len);
		}
		return ((width > (prefix_len + printed)) ? width : (prefix_len + printed));
	}

	f = get_func(spec, formats);
	if (f == NULL)
		return (print_unknown(format, start, *i));

	printed = f(args);
	if (width > printed)
		printed += repeat_char(' ', width - printed);
	return (printed);
}
