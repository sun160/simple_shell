#include "shell.h"

/**
 * _shellExit - exits the shell
 * @info: struct
 *  Return: exit status
 */
int _shellExit(info_s *info)
{
	int exitStats;

	if (info->argv[1])
	{
		exitStats = _eAtoi(info->argv[1]);
		if (exitStats == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_sputs(info->argv[1]);
			_sputchar('\n');
			return (1);
		}
		info->err_num = _eAtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * shellCd - changes the current directory of the process
 * @info: struct
 *  Return:  0
 */
int shellCd(info_s *info)
{
	char *i, *dire, buffer[1024];
	int changeDir;

	i = getcwd(buffer, 1024);
	if (!i)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dire = envInfo(info, "HOME=");
		if (!dire)
			changeDir =
				chdir((dire = envInfo(info, "PWD=")) ? dire : "/");
		else
			changeDir = chdir(dire);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!envInfo(info, "OLDPWD="))
		{
			_puts(i);
			_putchar('\n');
			return (1);
		}
		_puts(envInfo(info, "OLDPWD=")), _putchar('\n');
		changeDir =
			chdir((dire = envInfo(info, "OLDPWD=")) ? dire : "/");
	}
	else
		changeDir = chdir(info->argv[1]);
	if (changeDir == -1)
	{
		print_error(info, "can't cd to ");
		_sputs(info->argv[1]), _sputchar('\n');
	}
	else
	{
		init_env(info, "OLDPWD", envInfo(info, "PWD="));
		init_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shellHelp - changes the current directory
 * @info: Structure
 * Return: 0
 */
int shellHelp(info_s *info)
{
	char **args_array;

	args_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args_array);
	return (0);
}
