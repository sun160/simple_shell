#include "shell.h"

/**
 * histo - displays the history
 * @info: Structure
 *  Return:  0
 */
int histo(info_s *info)
{
	printList(info->history);
	return (0);
}

/**
 * unset_alias - remove alias
 * @info: parameter struct
 * @stri: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_s *info, char *stri)
{
	char *ptr, ch;
	int rs;

	ptr = _strchr(stri, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	rs = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, stri, -1)));
	*ptr = ch;
	return (rs);
}


/**
 * attach_alias - sets alias
 * @info:  struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int attach_alias(info_s *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - prints alias
 * @h: node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *h)
{
	char *p = NULL, *a = NULL;

	if (h)
	{
		p = _strchr(h->str, '=');
		for (a = h->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shellAlias - alias in shell
 * @info: Structure c
 *  Return: Always 0
 */
int shellAlias(info_s *info)
{
	int counter = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (counter = 1; info->argv[counter]; counter++)
	{
		ptr = _strchr(info->argv[counter], '=');
		if (ptr)
			attach_alias(info, info->argv[counter]);
		else
			print_alias(node_starts_with(info->alias, info->argv[counter], '='));
	}

	return (0);
}

