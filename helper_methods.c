#include "shell.h"

/**
 * interactive - shell mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_s *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 *_isalpha - checks for alpha char
 *@ch: char
 *Return: 1 for true, 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - checks char is a delimeter
 * @ch: char
 * @delimt: the delimeter string
 * Return: 1 for true, 0 for false
 */
int is_delim(char ch, char *delimt)
{
	while (*delimt)
		if (*delimt++ == ch)
			return (1);
	return (0);
}


/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return:integ
 */

int _atoi(char *s)
{
	int i;
	int res = 0;
	int mSign = -1;
	int breakstats = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			mSign = mSign * -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			res = res * 10;
			res -= (s[i] - '0');
			breakstats = 1;
		}
		else if (breakstats == 1)
			break;
	}
	res = mSign * res;
	return (res);
}

