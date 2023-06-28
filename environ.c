#include "shell.h"

/**
 * g_myenv - This prints the current environment
 * @info: This Structure contains potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int g_myenv(info_t *info)
{
	_print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This function gets the value of an environ variable
 * @info: This Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: This is the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * g_mysetenv - This Initialize a new environment variable,
 *             or modify an existing one
 * @info: This Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int g_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		g_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (g_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * g_myunsetenv - This Remove an environment variable
 * @info: This Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int g_myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		g_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		g_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _populate_env_list - This populates env linked list
 * @info: This Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

