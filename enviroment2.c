#include "shell.h"

/**
 * init_env - Init env
 * @info: Structure
 * @ch:  string env
 * @value:  string env value
 *  Return: Always 0
 */
int init_env(info_s *info, char *ch, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!ch || !value)
		return (0);

	buf = malloc(_strlen(ch) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, ch);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, ch);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


/**
 * get_envon - returns the string environ
 * @info: Structure
 * Return: Always 0
 */
char **get_envon(info_s *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _removeEnv - function removes env
 * @info: Structure
 * @var:  string env var
 * Return: 1 on removel, 0 otherwise
 */
int _removeEnv(info_s *info, char *var)
{
	list_t *node = info->env;
	size_t size = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), size);
			size = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		size++;
	}
	return (info->env_changed);
}
