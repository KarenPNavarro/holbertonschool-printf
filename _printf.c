#include "main.h"

static format_t formats[] = {
	{'c', print_char},
	{'s', print_string},
	{'%', print_percent},
	{'d', print_int},
	{'i', print_int},
	{'b', print_binary},
	{'u', print_unsigned},
	{'o', print_octal},
	{'x', print_hex_lower},
	{'X', print_hex_upper},
	{'S', print_S},
	{'p', print_pointer},
	{'\0', NULL}
};

/**
 * parse_flags - parses +, space and # flags
 * @format: format string
 * @i: index pointer (points to first char after '%', advanced past flags)
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 * @flags_start: first index of flags/spec to replay on unknown
 */
static void parse_flags(const char *format, int *i, int *plus, int *space,
		int *hash, int *flags_start)
{
	*flags_start = *i;
	while (format[*i] == '+' || format[*i] == ' ' || format[*i] == '#')
	{
		if (format[*i] == '+')
			*plus = 1;
		else if (format[*i] == ' ')
			*space = 1;
		else
			*hash = 1;
		(*i)++;
	}
}

/**
 * print_unknown - prints '%' followed by consumed flags and specifier
 * @format: format string
 * @start: start index (first flag or spec)
 * @end: end index (specifier)
 * @count: printed character count
 */
static void print_unknown(const char *format, int start, int end, int *count)
{
	int j;

	_buf_putc('%');
	(*count)++;
	j = start;
	while (j <= end)
	{
		_buf_putc(format[j]);
		(*count)++;
		j++;
	}
}

/**
 * apply_flag_prefix - prints prefix/sign required by supported flags
 * @spec: the conversion specifier
 * @args: the argument list (not consumed)
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 * @count: printed character count
 */
static void apply_flag_prefix(char spec, va_list args, int plus, int space,
		int hash, int *count)
{
	va_list peek;
	int n;
	unsigned int un;

	if ((spec == 'd' || spec == 'i') && (plus || space))
	{
		va_copy(peek, args);
		n = va_arg(peek, int);
		va_end(peek);
		if (n >= 0)
		{
			_buf_putc(plus ? '+' : ' ');
			(*count)++;
		}
		return;
	}

	if (!hash || (spec != 'o' && spec != 'x' && spec != 'X'))
		return;

	va_copy(peek, args);
	un = va_arg(peek, unsigned int);
	va_end(peek);
	if (un == 0)
		return;

	if (spec == 'o')
	{
		_buf_putc('0');
		(*count)++;
		return;
	}

	_buf_putc('0');
	_buf_putc(spec == 'x' ? 'x' : 'X');
	(*count) += 2;
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
	int plus;
	int space;
	int hash;
	int flags_start;
	int (*f)(va_list);
	char spec;

	plus = 0;
	space = 0;
	hash = 0;

	(*i)++;
	parse_flags(format, i, &plus, &space, &hash, &flags_start);
	if (format[*i] == '\0')
	{
		_buf_discard();
		return (-1);
	}
	spec = format[*i];

	f = get_func(spec, formats);
	if (f == NULL)
		print_unknown(format, flags_start, *i, count);
	else
	{
		apply_flag_prefix(spec, args, plus, space, hash, count);
		*count += f(args);
	}

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

	if (format == NULL)
		return (-1);

	va_start(args, format);
	i = 0;
	count = 0;

	while (format[i])
	{
		if (format[i] != '%')
		{
			_buf_putc(format[i]);
			count++;
		}
		else
		{
			if (handle_percent(format, &i, args, formats, &count) == -1)
			{
				_buf_discard();
				va_end(args);
				return (-1);
			}
		}
		i++;
	}
	if (_buf_flush() == -1)
	{
		_buf_discard();
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (count);
}
