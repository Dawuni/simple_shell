#include "shell.h"

/**
 * customAtoi - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: Converted number on success, -1 on error
 */

int customAtoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorMessage - prints an error message
 * @info: structure containing error information
 * @errorType: string containing specified error type
 */

void printErrorMessage(info_t *info, char *errorType)
{
	customPrint(info->fileName);
	customPrint(": ");
	customPrintInteger(info->lineNumber, STDERR_FILENO);
	customPrint(": ");
	customPrint(info->arguments[0]);
	customPrint(": ");
	customPrint(errorType);
}

/**
 * customPrintInteger - prints an integer to the specified file descriptor
 * @input: the integer to be printed
 * @fd: the file descriptor to write to
 *
 * Return: Number of characters printed
 */

int customPrintInteger(int input, int fd)
{
	int (*customPutchar)(char) = customPutchar;
	int index, count = 0;
	unsigned int absoluteValue, current;

	if (fd == STDERR_FILENO)
		customPutchar = customErrorPutchar;
	if (input < 0)
	{
		absoluteValue = -input;
		customPutchar('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absoluteValue / index)
		{
			customPutchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	customPutchar('0' + current);
	count++;

	return (count);
}

/**
 * convertToBase - converts a number to a specified base
 * @num: the number to convert
 * @base: the base to convert to
 * @flags: argument flags
 *
 * Return: String representation of the converted number
 */

char *convertToBase(long int num, int base, int flags)
{
	static char *characterArray;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	characterArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do
	{
		*--pointer = characterArray[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * removeFirstComment - replaces the first instance of '#' with '\0'
 * @string: address of the string to modify
 *
 * Return: Always 0
 */

void removeFirstComment(char *string)
{
	int index;

	for (index = 0; string[index] != '\0'; index++)
		if (string[index] == '#' && (!index || string[index - 1] == ' '))
		{
			string[index] = '\0';
			break;
		}
}

