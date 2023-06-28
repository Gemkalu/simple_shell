#include "shell.h"

/**
 * _list_len - This Function determines length of linked list
 * @h: This is a pointer to first node
 *
 * Return: The size of list
 */
size_t _list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings -This Function returns an array of strings of the list->str
 * @head: This is a pointer to first node
 *
 * Return: the array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = _list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(g_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _print_list - This function prints all elements of a list_t linked list
 * @h: This points to first node
 *
 * Return: The size of list
 */
size_t _print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		g_puts(convert_number(h->num, 10, 0));
		g_putchar(':');
		g_putchar(' ');
		g_puts(h->str ? h->str : "(nil)");
		g_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - This Function returns node whose string startswith prefix
 * @node: This points to list head
 * @prefix: This is a string to match
 * @c: This is the next character after prefix to match
 *
 * Return: the match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index - This Function gets the index of a node
 * @head: This points to list head
 * @node: This points to the node
 *
 * Return: the index of node or -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

