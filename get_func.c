#include "main.h"

/**
 * get_func - returns the function for a format specifier
 * @c: the format specifier character
 * @formats: array of format_t structs
 *
 * Return: pointer to the function or NULL
 */
int (*get_func(char c, format_t *formats))(va_list *)
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
