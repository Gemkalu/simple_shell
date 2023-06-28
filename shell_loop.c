#include "shell.h"

/**
 * _hsh - This funcion is the  main shell loop
 * @info: This is the the parameter & return info struct
 * @av: This is the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clear_info(info);
		if (_interactive(info))
			g_puts("$ ");
		g_eputchar(BUF_FLUSH);
		r = _get_input(info);
		if (r != -1)
		{
			_set_info(info, av);
			builtin_ret = _find_builtin(info);
			if (builtin_ret == -1)
				_find_cmd(info);
		}
		else if (_interactive(info))
			g_putchar('\n');
		_free_info(info, 0);
	}
	_write_history(info);
	_free_info(info, 1);
	if (!_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * _find_builtin - This function finds a builtin command
 * @info:  This is the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0  if builtin executed successfully,
 * 1  if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int _find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", g_myexit},
		{"env", g_myenv},
		{"help", g_myhelp},
		{"history", g_myhistory},
		{"setenv", g_mysetenv},
		{"unsetenv", g_myunsetenv},
		{"cd", g_mycd},
		{"alias", g_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (g_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd - This function finds a command in PATH
 * @info: This is the parameter & return info struct
 *
 * Return: void
 */
void _find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd(info);
	}
	else
	{
		if ((_interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_error(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd -This function forks a an exec thread to run cmd
 * @info: This is the parameter & return info struct
 *
 * Return: void
 */
void _fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_print_error(info, "Permission denied\n");
		}
	}
}

