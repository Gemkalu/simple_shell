#include "shell.h"

/**
 * _clear_info - This function initializes info_t struct
 * @info: This is the struct address
 */
void _clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _set_info - This funtion initializes info_t struct
 * @info: This is a struct address
 * @av: This is an argument vector
 */
void _set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		_replace_alias(info);
		_replace_vars(info);
	}
}

/**
 * _free_info - This function frees info_t struct fields
 * @info: This is a struct address
 * @all: This is true if freeing all fields
 */
void _free_info(info_t *info, int all)
{
	_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_free_list(&(info->env));
		if (info->history)
			_free_list(&(info->history));
		if (info->alias)
			_free_list(&(info->alias));
		_ffree(info->environ);
			info->environ = NULL;
		_bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		g_putchar(BUF_FLUSH);
	}
}
