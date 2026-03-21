#include "main.h"

#define PRINTF_BUF_SIZE 1024

static char printf_buf[PRINTF_BUF_SIZE];
static int printf_buf_i;

/**
 * _buf_flush - writes the current buffer to stdout
 *
 * Return: number of bytes written, or -1 on error
 */
int _buf_flush(void)
{
	int written;

	if (printf_buf_i <= 0)
		return (0);

	written = write(1, printf_buf, printf_buf_i);
	if (written == -1)
		return (-1);

	printf_buf_i = 0;
	return (written);
}

/**
 * _buf_discard - discards any buffered output
 */
void _buf_discard(void)
{
	printf_buf_i = 0;
}

/**
 * _buf_putc - buffers a single character
 * @c: character to buffer
 *
 * Return: 1 on success, or -1 on error
 */
int _buf_putc(char c)
{
	int rc;

	if (printf_buf_i >= PRINTF_BUF_SIZE)
	{
		rc = _buf_flush();
		if (rc == -1)
			return (-1);
	}

	printf_buf[printf_buf_i] = c;
	printf_buf_i++;
	return (1);
}

/**
 * _buf_write - buffers a string of length len
 * @s: string to buffer
 * @len: number of bytes to buffer
 *
 * Return: number of bytes buffered, or -1 on error
 */
int _buf_write(const char *s, int len)
{
	int i;

	if (s == NULL || len <= 0)
		return (0);

	i = 0;
	while (i < len)
	{
		if (_buf_putc(s[i]) == -1)
			return (-1);
		i++;
	}

	return (len);
}
