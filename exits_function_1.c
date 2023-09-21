#include "shell.h"


/**
 * _strncpy - Copies a string up to a specified len.
 * @dest: The destination str to be copied to.
 * @src: The source string to cpy.
 * @n: The number of characters to cpy.
 *
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int c, d;
	char *s = dest;

	c = 0;
	while (src[c] != '\0' && c < n - 1)
	{
		dest[c] = src[c];
		c++;
	}
	if (c < n)
	{
		d = c;
		while (d < n)
		{
			dest[d] = '\0';
			d++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified len.
 * @dest: The first str.
 * @src: The second str.
 * @n: The maximum num of bytes to use from source.
 *
 *
 * Return: A pointer to concatenated str.
 */
char *_strncat(char *dest, char *src, int n)
{
	int c, d;
	char *s = dest;

	c = 0;
	d = 0;
	while (dest[c] != '\0')
		c++;
	while (src[d] != '\0' && d < n)
	{
		dest[c] = src[d];
		c++;
		d++;
	}
	if (d < n)
		dest[c] = '\0';
	return (s);
}

/**
 * _strchr - Locates a char in the string.
 * @s: The str to be searched.
 * @c: The char to look out for.
 *
 *
 * Return: A ptr to the first occurrence of the char in the string,
 *		or NULL if the char is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
