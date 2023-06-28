#include "shell.h"

/**
 * main - This is the entry point
 * @ac: This is an arg count
 * @av: This is an arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				g_eputs(av[0]);
				g_eputs(": 0: Can't open ");
				g_eputs(av[1]);
				g_eputchar('\n');
				g_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populate_env_list(info);
	_read_history(info);
	_hsh(info, av);
	return (EXIT_SUCCESS);
}

