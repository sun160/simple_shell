#include "shell.h"

/**
 * find_path find path
 * @info: the info struct
 * @strPath: the path string
 * @sh: the shell to find
 * Return: full path
 */
char *find_path(info_s *info, char *strPath, char *sh)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!strPath)
		return (NULL);
	if ((_strlen(sh) > 2) && starts_with(sh, "./"))
	{
		if (is_excutable(info, sh))
			return (sh);
	}
	while (1)
	{
		if (!strPath[i] || strPath[i] == ':')
		{
			path = dup_chars(strPath, current_pos, i);
			if (!*path)
				_strcat(path, sh);
			else
			{
				_strcat(path, "/");
				_strcat(path, sh);
			}
			if (is_excutable(info, path))
				return (path);
			if (!strPath[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * is_excutable - checks if the file executable
 * @info: the info struct
 * @dir: dir to the file
 * Return: 1 if true, 0 otherwise
 */
int is_excutable(info_s *info, char *dir)
{
	struct stat stats;

	(void)info;
	if (!dir || stat(dir, &stats))
		return (0);

	if (stats.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @strPath: string path
 * @begining: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *strPath, int begining, int end)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (i = begining; i < end; i++)
		if (strPath[i] != ':')
			buf[j++] = strPath[i];
	buf[j] = 0;
	return (buf);
}
