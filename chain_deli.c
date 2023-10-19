#include "shell.h"

/**
 * isChainDel - test if current char is a chain
 * @info:  struct
 * @buf: buffer
 * @ptr: ptr
 * Return: 1 if delimeter, 0 otherwise
 */
int isChainDel(info_s *info, char *buf, size_t *ptr)
{
	size_t j = *ptr;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * checkChainDelm - checks chai
 * @info: struct
 * @buf: buffer
 * @ptr: ptr
 * @start: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void checkChainDelm(info_s *info, char *buf, size_t *ptr,
			 size_t start, size_t len)
{
	size_t tmp = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start] = 0;
			tmp = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start] = 0;
			tmp = len;
		}
	}

	*ptr = tmp;
}

/**
 * change_alias - change aliases
 * @info: struct
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_s *info)
{
	int i = 0;
	list_t *h;
	char *ptr;

	for (; i < 10; i++)
	{
		h = node_starts_with(info->alias, info->argv[0], '=');
		if (!h)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(h->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * changeVars - changes var
 * @info: struct
 * Return: 1 on changing, 0 otherwise
 */
int changeVars(info_s *info)
{
	int j = 0;
	list_t *h;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
				_strdup(convert_int(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
				_strdup(convert_int(getpid(), 10, 0)));
			continue;
		}
		h = node_starts_with(info->env, &info->argv[j][1], '=');
		if (h)
		{
			replace_string(&(info->argv[j]),
				_strdup(_strchr(h->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - change str
 * @past: address of past string
 * @current: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **past, char *current)
{
	free(*past);
	*past = current;
	return (1);
}

