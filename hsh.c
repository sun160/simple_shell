#include "shell.h"

/**
 * hsh - shell
 * @info: struct
 * @av: vector arg
 * Return: 0 on success, 1 on error
 */

int hsh(info_s *info, char **av)
{
	ssize_t size = 0;
	int builtin_res = 0;

	while (size != -1 && builtin_res != -2)
	{
		clear(info);
		if (interactive(info))
			_puts("$ ");
		_sputchar(BUF_FLUSH);
		size = getInput(info);
		if (size != -1)
		{
			init_info(info, av);
			builtin_res = find_builtin(info);
			if (builtin_res == -1)
				find_sh(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	writeHisto(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_res == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_res);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_s *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellExit},
		{"env", shellEnv},
		{"help", shellHelp},
		{"history", histo},
		{"setenv", initenv},
		{"unsetenv", removeEnv},
		{"cd", shellCd},
		{"alias", shellAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->ln_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_sh - finds command
 * @info:  struct
 * Return: void
 */
void find_sh(info_s *info)
{
	char *dir = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->ln_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	dir = find_path(info, envInfo(info, "PATH="), info->argv[0]);
	if (dir)
	{
		info->path = dir;
		fork_sh(info);
	}
	else
	{
		if ((interactive(info) || envInfo(info, "PATH=")
			|| info->argv[0][0] == '/') && is_excutable(info, info->argv[0]))
			fork_sh(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_sh - forks to r sh
 * @info: struct
 * Return: void
 */
void fork_sh(info_s *info)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("Error:");
		return;
	}
	if (pid_child == 0)
	{
		if (execve(info->path, info->argv, get_envon(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
