#include "shell.h"

/**
 * _strcpy - Copy a string
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to destination buffer
 */
char *_strcpy(char *dest, char *src)
{
	int p = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[p])
	{
		dest[p] = src[p];
		p++;
	}
	dest[p] = 0;
	return (dest);
}

/**
 * _strdup - Duplicate a string
 * @str: The string to be duplicated
 *
 * Return: Pointer to duplicate string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * _puts - Print an input str
 * @str: The string to print
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int p = 0;

	if (!str)
		return;
	while (str[p] != '\0')
	{
		_putchar(str[p]);
		p++;
	}
}

/**
 * _putchar - Write the character c to the standard output (stdout)
 * @c: The char to be printed
 *
 * Return: 1 On success, On error, -1 is returned,
 *	and errno is set appropriately.
 */
int _putchar(char c)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}
