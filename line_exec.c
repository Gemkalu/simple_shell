#include "shell.h"


/**
 * gsplitstring - it splits a string and makes it an array of pointers to words
 * @str: this is a  string to be split
 * @delim: this is the  delimiter
 * Return: These array of pointers to words
 */

char **gsplitstring(char *str, const char *delim)
{
	int i, wn;
	char **array;
	char *token;
	char *copy;

	copy = malloc(g_strlen(str) + 1);
	if (copy == NULL)
	{
		perror(_getenv("_"));
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';

	token = strtok(copy, delim);
	array = malloc((sizeof(char *) * 2));
	array[0] = g_strdup(token);

	i = 1;
	wn = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		array = g_realloc(array, (sizeof(char *) * (wn - 1)), (sizeof(char *) * wn));
		array[i] = g_strdup(token);
		i++;
		wn++;
	}
	free(copy);
	return (array);
}

/**
 * gexecute - This executes a command
 * @argv: These is an array of arguments
 */

void gexecute(char **argv)
{

	int d, status;

	if (!argv || !argv[0])
		return;
	d = fork();
	if (d == -1)
	{
		perror(_getenv("_"));
	}
	if (d == 0)
	{
		execve(argv[0], argv, environ);
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
}

/**
 * g_realloc - This Reallocates memory block
 * @ptr:This is a previous pointer
 * @old_size: An old size of previous pointer
 * @new_size: A new size for our pointer
 * Return: A New resized Pointer
 */

void *g_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *old;

	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);
	old = ptr;
	if (new == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];
		free(ptr);
		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * gfreearv - frees the array of pointers arv
 * @arv: array of pointers
 */

void gfreearv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
}

