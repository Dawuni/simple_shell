#include "shell.h"

/**
 * copyString - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *copyString(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == NULL)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

/**
 * duplicateString - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicateString(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * printString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		writeCharacter(str[i]);
		i++;
	}
}

/**
 * writeCharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacter(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
