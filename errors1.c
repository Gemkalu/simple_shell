#include "shell.h"

/**
 * g_erratoi - This function converts a string to an integer
 * @s: This is the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int g_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _print_error - This prints an error message
 * @info: This is the parameter & return info struct
 * @estr: This string contains specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _print_error(info_t *info, char *estr)
{
	g_eputs(info->fname);
	g_eputs(": ");
	_print_d(info->line_count, STDERR_FILENO);
	g_eputs(": ");
	g_eputs(info->argv[0]);
	g_eputs(": ");
	g_eputs(estr);
}

/**
 * _print_d - This function prints a decimal (integer) number (base 10)
 * @input: This is the input
 * @fd: This is the filedescriptor to write to
 *
 * Return: This is the number of characters printed
 */
int _print_d(int input, int fd)
{
	int (*_g_putchar)(char) = g_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_g_putchar = g_eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		_g_putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_g_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	_g_putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - This is a converter function, a clone of itoa
 * @num: This is the number
 * @base: This is the base
 * @flags: This is the argument flags
 *
 * Return: This is a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _remove_comments - This is function replaces first instance of '#' with '\0'
 * @buf: This address of the string to modify
 *
 * Return: Always 0;
 */
void _remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

