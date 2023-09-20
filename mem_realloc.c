#include "shell.h"

/**
 * setMemory - fills a memory block with a specified byte value
 * @dest: the destination memory block
 * @value: the byte value to fill the memory with
 * @length: the number of bytes to fill
 * Return: a pointer to the destination memory block
 */
char *setMemory(char *dest, char value, unsigned int length)
{
	unsigned int i;

	for (i = 0; i < length; i++)
	{
		dest[i] = value;
	}
	return (dest);
}

/**
 * freeStringArray - frees a dynamically allocated array of strings
 * @strArray: the array of strings
 */
void freeStringArray(char **strArray)
{
	char **temp = strArray;

	if (!strArray)
		return;
	while (*strArray)
		free(*strArray++);
	free(temp);
}

/**
 * resizeMemoryBlock - resizes a memory block and preserves its content
 * @ptr: pointer to the previous memory block
 * @oldSize: size of the previous memory block in bytes
 * @newSize: size of the new memory block in bytes
 *
 * Return: pointer to the new memory block
 */
void *resizeMemoryBlock(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (newPtr);
}
