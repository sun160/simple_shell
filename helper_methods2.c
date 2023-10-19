#include "shell.h"

/**
 * print_error - prints errors
 * @info: return info struct
 * @strErr: specified error type
 * Return: void
 */
void print_error(info_s *info, char *strErr)
{
	_sputs(info->fileName);
	_sputs(": ");
	print_decimal(info->ln_count, STDERR_FILENO);
	_sputs(": ");
	_sputs(info->argv[0]);
	_sputs(": ");
	_sputs(strErr);
}

/**
 * _eAtoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no nums , result on success or -1 -1 on error
 */
int _eAtoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * ignore_comment - ignore comments
 * @comment: address of the string to modify
 * Return:  void;
 */
void ignore_comment(char *comment)
{
	int i = 0;

	for (; comment[i] != '\0'; i++)
		if (comment[i] == '#' && (!i || comment[i - 1] == ' '))
		{
			comment[i] = '\0';
			break;
		}
}


/**
 * print_decimal - function prints a decimal
 * @in: the in
 * @fd: file descriptor
 * Return: number of characters printed
 */
int print_decimal(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int size, counter = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _sputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (size = 1000000000; size > 1; size /= 10)
	{
		if (_abs_ / size)
		{
			__putchar('0' + current / size);
			counter++;
		}
		current %= size;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_int - converter int to str
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_int(long int num, int base, int flags)
{
	static char buffer[50];
	static char *alpha;
	char negative = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		negative = '-';

	}
	alpha = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = alpha[n % base];
		n /= base;
	} while (n != 0);

	if (negative)
		*--ptr = negative;
	return (ptr);
}
