#include "shell.h"


/**
 * _eputs - Prints an input string to std error.
 * @str: The string to  print.
 *
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		n++;
	}
}

/**
 * _eputchar - Writes the char 'c' to std error.
 * @c: The char to print.
 *
 *
 * Return: On success, 1.
 *	On error, -1 is returned, and errno is set appro.
 */
int _eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putfd - Writes the char 'c' to the file descriptor.
 * @c: The characters to print.
 * @fd: The file descriptor to be written to.
 *
 *
 * Return: On success, 1.
 *	On error, -1 is returned, and errno is set app.
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to be written to.
 *
 *
 * Return: The num of characters written.
 */
int _putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += _putfd(*str++, fd);
	}
	return (n);
}
