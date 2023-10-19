#include "shell.h"

/**
 **_memset - fills memory with bytes
 *@s: ptr
 *@chrByte: the byte to fill ptr
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory.
 */
char *_memset(char *s, char chrByte, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n; i++)
		s[i] = chrByte;
	return (s);
}

/**
 * ptrFree - frees a pointer and set add to null
 * @ptr: pointer to be free
 *
 * Return: 1 on success, otherwise 0.
 */
int ptrFree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * strFree - frees string.
 * @ptrStr: string to be freed
 */
void strFree(char **ptrStr)
{
	char **s = ptrStr;

	if (!ptrStr)
		return;
	while (*ptrStr)
		free(*ptrStr++);
	free(s);
}

/**
 * *_realloc - reallocates memory
 * @ptr: pointer
 * @old_size: old size
 * @new_size: new size
 * Return: pointer to the new memory
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	new_ptr = malloc(new_size);

	if (new_ptr == NULL)
		return (NULL);

	old_ptr = ptr;

	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new_ptr[i] = old_ptr[i];
	}

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new_ptr[i] = old_ptr[i];
	}

	free(ptr);
	return (new_ptr);
}
