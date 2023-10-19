#include "shell.h"

/**
 * init_info - initializes info_s
 * @info: struct address
 * @av: argument vector
 */
void init_info(info_s *info, char **av)
{
	int j = 0;

	info->fileName = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		change_alias(info);
		changeVars(info);
	}
}

/**
 * clear - initializes info_s struct
 * @data: struct address
 */
void clear(info_s *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * free_info - frees info_s
 * @info: struct ptr
 * @stat: int
 */
void free_info(info_s *info, int stat)
{
	strFree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (stat)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		strFree(info->environ);
			info->environ = NULL;
		ptrFree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

