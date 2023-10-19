#include "shell.h"

/**
 * getHistoFile - gets the history file
 * @info:  struct
 * Return: history file
 */

char *getHistoFile(info_s *info)
{
	char *buf, *directory;

	directory = envInfo(info, "HOME=");
	if (!directory)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, directory);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * writeHisto - creates a histo file
 * @info: struct
 * Return: 1 on success
 */
int writeHisto(info_s *info)
{
	ssize_t fd;
	char *filename = getHistoFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_sputsfd(node->str, fd);
		_sput_fd('\n', fd);
	}
	_sput_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * assignNumHistory - assign nums to the history linked list after changes
 * @info: Structure
 * Return: n histo count
 */
int assignNumHistory(info_s *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}


/**
 * read_history - reads history  file
 * @info: the parameter struct
 * Return: count on success
 */
int read_history(info_s *info)
{
	int counter, last = 0, lnNumber = 0;
	ssize_t fd, rdlengh, isize = 0;
	struct stat stats;
	char *buf = NULL, *filename = getHistoFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &stats))
		isize = stats.st_size;
	if (isize < 2)
		return (0);
	buf = malloc(sizeof(char) * (isize + 1));
	if (!buf)
		return (0);
	rdlengh = read(fd, buf, isize);
	buf[isize] = 0;
	if (rdlengh <= 0)
		return (free(buf), 0);
	close(fd);
	for (counter = 0; counter < isize; counter++)
		if (buf[counter] == '\n')
		{
			buf[counter] = 0;
			creatHistoList(info, buf + last, lnNumber++);
			last = counter + 1;
		}
	if (last != counter)
		creatHistoList(info, buf + last, lnNumber++);
	free(buf);
	info->histcount = lnNumber;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	assignNumHistory(info);
	return (info->histcount);
}

/**
 * creatHistoList - build histo list
 * @info: Structure
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int creatHistoList(info_s *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
