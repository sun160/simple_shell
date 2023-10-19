#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to check the length
 * Return: the length of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}


/**
 * _strcmp - function compares of two string.
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * starts_with - checks if keystr starts with strSearch
 * @strSearch: string to search
 * @keystr: the substring to find
 *
 * Return: address of next char of strSearch or NULL
 */
char *starts_with(const char *strSearch, const char *keystr)
{
	while (*keystr)
		if (*keystr++ != *strSearch++)
			return (NULL);
	return ((char *)strSearch);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
