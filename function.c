#include "shell.h"

/**
 * customPrintError - prints an error message
 * @errorMessage: the error message to be printed
 *
 * Return: Nothing
 */

void customPrintError(char *errorMessage)
{
	int index = 0;

	if (!errorMessage)
		return;
	while (errorMessage[index] != '\0')
	{
		customPrintCharacter(errorMessage[index]);
		index++;
	}
}

/**
 * customPrintCharacter - writes the character c to the custom file descriptor
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int customPrintCharacter(char character)
{
	static int index;
	static char buffer[CUSTOM_WRITE_BUF_SIZE];

	if (character == CUSTOM_BUF_FLUSH || index >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(CUSTOM_FILE_DESCRIPTOR, buffer, index);
		index = 0;
	}
	if (character != CUSTOM_BUF_FLUSH)
	buffer[index++] = character;
	return (1);
}

/**
 * customPrintToFileDescriptor - writes the character c to the given file
 * @character: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int customPrintToFileDescriptor(char character, int fileDescriptor)
{
	static int index;
	static char buffer[CUSTOM_WRITE_BUF_SIZE];

	if (character == CUSTOM_BUF_FLUSH || index >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(fileDescriptor, buffer, index);
		index = 0;
	}
	if (character != CUSTOM_BUF_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * customPrintStringToFileDescriptor - prints an input string to
 *	the given file descriptor
 * @inputString: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */

int customPrintStringToFileDescriptor(char *inputString, int fileDescriptor)
{
	int index = 0;

	if (!inputString)
		return (0);
	while (*inputString)
	{
		index += customPrintToFileDescriptor(*inputString++,
				fileDescriptor);
	}
	return (index);
}
