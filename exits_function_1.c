#include "shell.h"

/**
 * customStringCopy - copies a source string to a destination string
 * @destination: the destination string
 * @source: the source string
 * @n: the maximum number of characters to copy
 *
 * Return: The destination string after copying
 */

char *customStringCopy(char *destination, char *source, int n)
{
	int index, j;
	char *result = destination;

	index = 0;
	while (source[index] != '\0' && index < n - 1)
	{
		destination[index] = source[index];
		index++;
	}
	if (index < n)
	{
		j = index;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * customStringConcatenate - concatenates two strings with a maximum limit
 * @destination: the destination string
 * @source: the source string
 * @n: the maximum number of characters to concatenate
 *
 * Return: The concatenated string in the destination
 */

char *customStringConcatenate(char *destination, char *source, int n)
{
	int index1, index2;
	char *result = destination;

	index1 = 0;
	while (destination[index1] != '\0')
		index1++;
	index2 = 0;
	while (source[index2] != '\0' && index2 < n)
	{
		destination[index1] = source[index2];
		index1++;
		index2++;
	}
	if (index2 < n)
		destination[index1] = '\0';
	return (result);
}

/**
 * customStringFindCharacter - finds a character in a string
 * @string: the string to search in
 * @character: the character to look for
 *
 * Return: A pointer to the first occurrence of the character in the string
 *         or NULL if not found
 */

char *customStringFindCharacter(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
