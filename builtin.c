#include "shell.h"

/**
 * g_myexit - This function exits the shell
 * @info: This is a Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int g_myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = g_erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			_print_error(info, "Illegal number: ");
			g_eputs(info->argv[1]);
			g_eputchar('\n');
			return (1);
		}
		info->err_num = g_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * g_mycd - This fuction changes the current directory of the process
 * @info: This is a Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int g_mycd(info_t *info)
{
	char *current_dir, *dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		g_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (g_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			g_puts(current_dir);
			g_putchar('\n');
			return (1);
		}
		g_puts(_getenv(info, "OLDPWD="));
		g_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_print_error(info, "can't cd to ");
		g_eputs(info->argv[1]);
		g_eputchar('\n');
	}
	else
	{
		g_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		g_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * g_myhelp - This function changes the current directory of the process
 * @info: This is a structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int g_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	g_puts("help call works. Function not yet implemented \n");
	if (0)
		g_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

