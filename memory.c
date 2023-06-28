#include "shell.h"

/**
 * _bfree - This functions frees a pointer and NULLs the address
 * @ptr: This is an address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

