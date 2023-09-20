#include "shell.h"

/**
 * freeAndNull - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if the pointer was freed, 0 otherwise.
 */
int freeAndNull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
