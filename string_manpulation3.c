#include "shell.h"

/**
 * _strcpy - copies the content of string
 * @d: destination of string
 * @s: source of string
 * Return: pointer to destination
 */
char *_strcpy(char *d, char *s)
{
	int y = 0;

	if (d == s || s == 0)
		return (d);
	while (s[y])
	{
		d[y] = s[y];
		y++;
	}
	d[y] = 0;
	return (d);
}


/**
 **_strncpy - copies a string
 *@dest:destination of string
 *@src: source of  string
 *@charCount: number of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int charCount)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < charCount - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < charCount)
	{
		j = i;
		while (j < charCount)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}


/**
 * _strcat - concatenates two strings
 * @d: the destination
 * @s: the source
 *
 * Return: pointer to destination
 */

char *_strcat(char *d, char *s)
{
	char *ptr = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (ptr);
}


/**
 **_strncat - concatenates of one string to another.
 *@f: the first string
 *@src: the second string
 *@b: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *f, char *src, int b)
{
	int y, g;
	char *s = f;

	y = 0;
	g = 0;
	while (f[y] != '\0')
		y++;
	while (src[g] != '\0' && g < b)
	{
		f[y] = src[g];
		y++;
		g++;
	}
	if (g < b)
		f[y] = '\0';
	return (s);
}
