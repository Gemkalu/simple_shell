#include "shell.h"

/**
 * input_buf - This buffers chained commands
 * @info: This is a parameter struct
 * @buf: This is an address of a buffer
 * @len: This is an address of a len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = g_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			_remove_comments(*buf);
			_build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _get_input - This gets a line minus the newline
 * @info: This is a parameter struct
 *
 * Return: bytes read
 */
ssize_t _get_input(info_t *info)
{
	static char *buf; /* the ';' This commands the chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	g_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* with this we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* This get pointer for return */

		_check_chain(info, buf, &j, i, len);
		while (j < len) /* This iterate to semicolon or end */
		{
			if (_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /*This increment past nulled ';'' */
		if (i >= len) /* This reached end of buffer? */
		{
			i = len = 0; /* This reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* This pass back pointer to current command position */
		return (g_strlen(p)); /* This return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - This  reads a buffer
 * @info: This is a  parameter struct
 * @buf: This is a buffer
 * @i: This is  size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * g_getline - This gets the next line of input from STDIN
 * @info: This is a parameter struct
 * @ptr: This is an address of pointer to buffer, preallocated or NULL
 * @length: This is a size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int g_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
	g_puts("\n");
	g_puts("$ ");
	g_putchar(BUF_FLUSH);
}
