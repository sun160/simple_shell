#include "shell.h"

/**
 * addStartingNode - adds a node start
 * @head: head node address ptr
 * @str: str
 * @num: node index
 * Return: size of list
 */
list_t *addStartingNode(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (head == NULL)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str != NULL)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		if (!h->str)
		{
			_puts("(nil)");
		}
		else
		{
			_puts(h->str);
			_puts("\n");
		}
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * delete_node_at_index - deletes node by index
 * @head: head ptr
 * @indx: index
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int indx)
{
	list_t *node, *prev_node;
	unsigned int tmp = 0;

	if (!head || !*head)
		return (0);

	if (!indx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (tmp == indx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		tmp++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *tmp, *node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	tmp = head;
	while (tmp)
	{
		node = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = node;
	}
	*head_ptr = NULL;
}

