#include "shell.h"

/**
 * _sputchar - writes the character standerd output
 * @ch: The character to print
 * Return: On success 1.
 */
int _sputchar(char ch)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[j++] = ch;
	return (1);
}

/**
 *_sputs - prints  input str
 * @str:  string
 * Return: void
 */
void _sputs(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		_sputchar(str[i]);
		i++;
	}
}


/**
 * _sput_fd - writes the character ch to given fd
 * @ch: The character to print
 * @fd: The filedescriptor
 * Return: On success 1.
 */
int _sput_fd(char ch, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 *_sputsfd - prints  string
 * @str: the string to print
 * @fd: the filedescriptor to write to
 * Return: chars number
 */
int _sputsfd(char *str, int fd)
{
	int tmp = 0;

	if (!str)
		return (0);
	while (*str)
	{
		tmp += _sput_fd(*str++, fd);
	}
	return (tmp);
}
