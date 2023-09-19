#include "shell.h"

/**
 * Interactive_Mode - returns true if shell is in interactive mode
 * @shellInfo: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int Interactive_Mode(shellInfo_t *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->fileDescriptor <= 2);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @character: the character to be checked
 * @delimiterStr: the delimiter string
 * Return: 1 if true, 0 if false
 */

int isDelimiter(char character, char *delimiterStr)
{
	while (*delimiterStr)
		if (*delimiterStr++ == character)
			return (1);
	return (0);
}

/**
 * isAlpha - checks for an alphabetic character
 * @character: The character to be check
 * Return: 1 if character is alphabetic, 0 otherwise
 */

int isAlpha(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertStringToInteger - converts a string to an integer
 * @inputStr: the string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int convertStringToInteger(char *inputString)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; inputStr[i] != '\0' && flag != 2; i++)
	{
		if (inputStr[i] == '-')
			sign *= -1;

		if (inputStr[i] >= '0' && inputStr[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (inputStr[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
