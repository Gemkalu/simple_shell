#include "shell.h"

/**
 * _interactive - This returns true if shell is in interactive mode
 * @info: This is a struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int _interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _is_delim - This checks if character is a delimiter
 * @c: This is the character to check
 * @delim: This is the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int _is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * g_isalpha - This checks for alphabetic character
 * @c: This is The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int g_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * g_atoi - This converts a string to an integer
 * @s: This is the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int g_atoi(char *s)
{
	int sign = 1;
	unsigned int result = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 1;
			result += (s[i] - '0');
		}
		else
		{
			break;
		}
		i++;
	}

	if (sign == -1)
		return (-result);
	else
		return (result);
}

