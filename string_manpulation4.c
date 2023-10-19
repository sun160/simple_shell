#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @g: the input string
 * @sp: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *g, char *sp)
{
	int y, j, t, r, w = 0;
	char **s;

	if (g == NULL || g[0] == 0)
		return (NULL);
	if (!sp)
		sp = " ";
	for (y = 0; g[y] != '\0'; y++)
		if (!is_delim(g[y], sp) && (is_delim(g[y + 1], sp) || !g[y + 1]))
			w++;

	if (w == 0)
		return (NULL);
	s = malloc((1 + w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, j = 0; j < w; j++)
	{
		while (is_delim(g[y], sp))
			y++;
		t = 0;
		while (!is_delim(g[y + t], sp) && g[y + t])
			t++;
		s[j] = malloc((t + 1) * sizeof(char));
		if (!s[j])
		{
			for (t = 0; t < j; t++)
				free(s[t]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < t; r++)
			s[j][r] = g[y++];
		s[j][r] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @sp: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *string, char sp)
{
	int y, j, t, m, w = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (y = 0; string[y] != '\0'; y++)
		if ((string[y] != sp && string[y + 1] == sp) ||
		    (string[y] != sp && !string[y + 1]) || string[y + 1] == sp)
			w++;
	if (w == 0)
		return (NULL);
	s = malloc((1 + w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, j = 0; j < w; j++)
	{
		while (string[y] == sp && string[y] != sp)
			y++;
		t = 0;
		while (string[y + t] != sp && string[y + t] && string[y + t] != sp)
			t++;
		s[j] = malloc((t + 1) * sizeof(char));
		if (!s[j])
		{
			for (t = 0; t < j; t++)
				free(s[t]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < t; m++)
			s[j][m] = string[y++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
