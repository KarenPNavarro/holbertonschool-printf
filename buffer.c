#include "main.h"

#define PRINTF_BUF_SIZE 1024

/**
 * struct buf_state_s - internal printf buffer state
 * @buf: buffer storage
 * @i: current index
 */
typedef struct buf_state_s
{
	char buf[PRINTF_BUF_SIZE];
	int i;
} buf_state_t;

static buf_state_t *buf_state(void)
{
	static buf_state_t st;

	return (&st);
}

/**
 * _buf_flush - writes the current buffer to stdout
 *
 * Return: number of bytes written, or -1 on error
 */
int _buf_flush(void)
{
	buf_state_t *st;
	int written;

	st = buf_state();

	if (st->i <= 0)
		return (0);

	written = write(1, st->buf, st->i);
	if (written == -1)
		return (-1);

	st->i = 0;
	return (written);
}

/**
 * _buf_discard - discards any buffered output
 */
void _buf_discard(void)
{
	buf_state_t *st;

	st = buf_state();
	st->i = 0;
}

/**
 * _buf_putc - buffers a single character
 * @c: character to buffer
 *
 * Return: 1 on success, or -1 on error
 */
int _buf_putc(char c)
{
	buf_state_t *st;
	int rc;

	st = buf_state();

	if (st->i >= PRINTF_BUF_SIZE)
	{
		rc = _buf_flush();
		if (rc == -1)
			return (-1);
	}

	st->buf[st->i] = c;
	st->i++;
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
