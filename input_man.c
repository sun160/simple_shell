#include "shell.h"

/**
 * inputBuffer - buffers commands
 * @info: struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes
 */
ssize_t inputBuffer(info_s *info, char **buf, size_t *len)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signtHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		i = _getline(info, buf, &len_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0';
				i--;
			}
			info->linecount_flag = 1;
			ignore_comment(*buf);
			creatHistoList(info, *buf, info->histcount++);
			{
				*len = i;
				info->cmd_buf = buf;
			}
		}
	}
	return (i);
}

/**
 * getInput - gets line
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t getInput(info_s *info)
{
	static char *buf;
	static size_t si, i, len;
	ssize_t ip = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	ip = inputBuffer(info, &buf, &len);
	if (ip == -1)
		return (-1);
	if (len)
	{
		i = si;
		p = buf + si;
		checkChainDelm(info, buf, &i, si, len);
		while (i < len)
		{
			if (isChainDel(info, buf, &i))
				break;
			i++;
		}

		si = i + 1;
		if (si >= len)
		{
			si = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (ip);
}

/**
 * read_buf - reads a buffer
 * @info: struct
 * @buf: buffer
 * @size: size
 *
 * Return: r
 */
ssize_t read_buf(info_s *info, char *buf, size_t *size)
{
	ssize_t tmp = 0;

	if (*size)
		return (0);
	tmp = read(info->readfd, buf, READ_BUF_SIZE);
	if (tmp >= 0)
		*size = tmp;
	return (tmp);
}

/**
 * _getline - gets the next line
 * @info: struct
 * @ptr: ptr
 * @length: size of pt
 * Return: s
 */
int _getline(info_s *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	s += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * signtHandler - sign
 * @sign_num: the signal number
 * Return: void
 */
void signtHandler(__attribute__((unused))int sign_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

