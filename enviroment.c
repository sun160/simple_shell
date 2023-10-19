#include "shell.h"
/**
 * initenv - initenve
 * @info: string
 *
 * Return: 1 on success, 0 on fail
*/

int initenv(info_s *info)
{
	if (info->argc != 3)
	{
		_sputs("Incorrect number of arguements\n");
		return (1);
	}
	if (init_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shellEnv - prints the current environment
 * @info: Structure
 * Return: Always 0
 */
int shellEnv(info_s *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * envInfo - gets env
 * @info: Structure
 * @name: env  name
 * Return:  value
 */
char *envInfo(info_s *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * initenv - init env
 * @info: Structure
 *  Return: Always 0
 */

/**
 * fillEnvList-  function fills env  list
 * @info: Structure
 * Return: Always 0
 */
int fillEnvList(info_s *info)
{
	list_t *node = NULL;
	size_t size;

	for (size = 0; environ[size]; size++)
		add_node_end(&node, environ[size], 0);
	info->env = node;
	return (0);
}

/**
 * removeEnv - Remove env variable
 * @info: Structure
 *  Return: Always 0
 */
int removeEnv(info_s *info)
{
	int j;

	if (info->argc == 1)
	{
		_sputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_removeEnv(info, info->argv[j]);

	return (0);
}
