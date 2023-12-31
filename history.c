#include "shell.h"

/**
 * get_history_file - This Function gets the history file
 * @info: This is a parameter struct
 *
 * Return: This is allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (g_strlen(dir) + g_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * _write_history - This Function creates a file,or appends to an existing file
 * @info: This is the parameter struct
 *
 * Return: 1 on success, else -1
 */
int _write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		g_putsfd(node->str, fd);
		g_putfd('\n', fd);
	}
	g_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _read_history - This Function reads history from file
 * @info: This is the parameter struct
 *
 * Return: This is histcount on success, 0 otherwise
 */
int _read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		_delete_node_at_index(&(info->history), 0);
	_renumber_history(info);
	return (info->histcount);
}

/**
 * _build_history_list - This function adds entry to a history linked list
 * @info: This is a Structure containing potential arguments. Used to maintain
 * @buf: This is the  buffer
 * @linecount: This is the history linecount, histcount
 *
 * Return: Always 0
 */
int _build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _renumber_history - This funtion renumbers history linked list after changes
 * @info: This structure contains potential arguments. Used to maintain
 *
 * Return: new histcount
 */
int _renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
