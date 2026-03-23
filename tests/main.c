#include <stdio.h>
#include "../main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	_printf("%b\n", 98);
	printf("%s\n", "1100010");
	_printf("%S\n", "Best\nSchool");
	printf("%s\n", "Best\\x0ASchool");
	_printf("%+d % d\n", 42, 42);
	printf("%+d % d\n", 42, 42);
	_printf("%#x %#X %#o\n", 42, 42, 42);
	printf("%#x %#X %#o\n", 42, 42, 42);
	_printf("[%.0d][%+.0d][% .0d]\n", 0, 0, 0);
	printf("[%.0d][%+.0d][% .0d]\n", 0, 0, 0);
	_printf("[%.5d][%.3u]\n", 42, 7);
	printf("[%.5d][%.3u]\n", 42, 7);
	_printf("[%.0x][%#.0x][%#.0o]\n", 0, 0, 0);
	printf("[%.0x][%#.0x][%#.0o]\n", 0, 0, 0);
	_printf("[%.3s][%.0s]\n", "Holberton", "Holberton");
	printf("[%.3s][%.0s]\n", "Holberton", "Holberton");

	_printf("[%05d][%05d][%+05d][% 05d]\n", 42, -42, 42, 42);
	printf("[%05d][%05d][%+05d][% 05d]\n", 42, -42, 42, 42);
	_printf("[%05.3d][%010.0u]\n", 7, 0);
	printf("[%05.3d][%010.0u]\n", 7, 0);
	_printf("[%#08x][%#08X][%#06o]\n", 42, 42, 42);
	printf("[%#08x][%#08X][%#06o]\n", 42, 42, 42);
	_printf("[%-5d][%-5d][%-+5d][%- 5d]\n", 42, -42, 42, 42);
	printf("[%-5d][%-5d][%-+5d][%- 5d]\n", 42, -42, 42, 42);
	_printf("[%-05d][%-#8x][%-#8o]\n", 42, 42, 42);
	printf("[%-05d][%-#8x][%-#8o]\n", 42, 42, 42);
	_printf("[%-10.3u][%-8.0x][%-#8.0o]\n", 7, 0, 0);
	printf("[%-10.3u][%-8.0x][%-#8.0o]\n", 7, 0, 0);
	_printf("[%-5s][%-3c][%-5%]\n", "hi", 'A', 0);
	printf("[%-5s][%-3c][%-5%]\n", "hi", 'A', 0);
	_printf("[%r][%10r]\n", "Holberton", "abc");
	printf("[%s][%10s]\n", "notrebloH", "cba");
	_printf("[%r]\n", NULL);
	printf("[%s]\n", ")llun(");

	return (0);
}
