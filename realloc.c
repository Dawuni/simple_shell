#include "shell.h"


/**
 * _memset - Fills memory with constant byte
 * @s: Pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The amount of bytes to fill
 *
 * Return: A pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}

/**
 * ffree - Frees a string from strings
 * @pp: String of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates a bloock of memory
 * @ptr: Pointer to the previous malloc'ated bloock
 * @old_size: Byte size of the previous bloock
 * @new_size: Byte size of the new bloock
 *
 * Return: Pointer to old block if successful, NULL otherwise.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
