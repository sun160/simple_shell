#include "shell.h"


/**
 * _strdup - duplicates a string
 * @q: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *q)
{
	int l = 0;
	char *y;

	if (q == NULL)
		return (NULL);
	while (*q++)
		l++;
	y = malloc(sizeof(char) * (l + 1));
	if (!y)
		return (NULL);
	for (l++; l--;)
		y[l] = *--q;
	return (y);
}

/**
 **_strchr - searches of character in a string
 *@g: the string to be searched
 *@s: the character to look for
 *Return: pointer to the character
 */
char *_strchr(char *g, char s)
{
	do {
		if (*g == s)
			return (g);
	} while (*g++ != '\0');

	return (NULL);
}

/**
 * _putchar - function writes the character s to stdout
 * @t: The character to print
 * Return: On success 1 , On error, -1 is returned.
 */
int _putchar(char t)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (t == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buf, u);
		u = 0;
	}
	if (t != BUF_FLUSH)
		buf[u++] = t;
	return (1);
}
