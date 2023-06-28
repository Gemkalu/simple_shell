#include "shell.h"

/**
 * g_eputs - This  prints an input string
 * @str: This is the string to be printed
 *
 * Return: Nothing
 */
void g_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		g_eputchar(str[i]);
		i++;
	}
}

/**
 * g_eputchar - This writes the character c to stderr
 * @c: This is the character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int g_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * g_putfd - This writes the character c to given fd
 * @c: This is the character to print
 * @fd: This is The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int g_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * g_putsfd - This is prints an input string
 * @str: This is the string to be printed
 * @fd: This is the filedescriptor to write to
 *
 * Return: This is the number of chars put
 */
int g_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += g_putfd(*str++, fd);
	}
	return (i);
}

