#include "shell.h"

/**
 * g_strlen - This function returns the length of a string
 * @s: This is the string whose length to check
 *
 * Return: the integer length of string
 */
int g_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * g_strcmp - This function performs lexicogarphic comparison of two strangs.
 * @s1: This is the first strang
 * @s2: This is the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int g_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - This function checks if needle starts with haystack
 * @haystack: This is the string to search
 * @needle: This is the substring to find
 *
 * Return: This is an address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This function concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 *
 * Return: This points to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

