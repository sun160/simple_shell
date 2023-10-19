#include "shell.h"


/**
 * listStrings - get strings array of the list str
 * @h: ptr of first node
 * Return: arr of strings
 */
char **listStrings(list_t *h)
{
	list_t *node = h;
	size_t size = list_length(h), i_size;
	char **strings;
	char *string;

	if (!h || !size)
		return (NULL);
	strings = malloc(sizeof(char *) * (size + 1));
	if (!strings)
		return (NULL);
	for (size = 0; node; node = node->next, size++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (i_size = 0; i_size < size; i_size++)
				free(strings[i_size]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, node->str);
		strings[size] = string;
	}
	strings[size] = NULL;
	return (strings);
}

/**
 * list_length - linked list length
 * @head: ptr to first node
 * Return:  list length
 */
size_t list_length(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		head = head->next;
		size++;
	}
	return (size);
}


/**
 * node_starts_with - returns node who starts with prefix
 * @node: pointer to list head
 * @str: string to match
 * @ch: next char prefix
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *str, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, str);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * printList - prints all elements of a list_t linked list
 * @head: ptr to first node
 * Return: size of list
 */
size_t printList(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		_puts(convert_int(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		size++;
	}
	return (size);
}


/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t size = 0;

	while (head)
	{
		if (head == node)
			return (size);
		head = head->next;
		size++;
	}
	return (-1);
}

