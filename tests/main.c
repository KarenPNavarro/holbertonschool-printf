#include <stdio.h>
#include "../main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	_printf("%b\n", 98);
	printf("%s\n", "1100010");
	_printf("%S\n", "Best\nSchool");
	printf("%s\n", "Best\\x0ASchool");

	return (0);
}
