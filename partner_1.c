#include "shell.h"

/**
 * _strcmp - perform a comparison between two strings.
 * @str1: string to be compared first.
 * @str2: string to be compared second
 *
 * Return: difference of the two strings
 */

int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while  (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			break;
		i++;
	}
	return (str1[i] - str2[i]);
}

/**
 * _strcat - concatenates two strings.
 * @dest: string to be concatenated to.
 * @src:  string to concatenate.
 *
 * Return: address of the new string.
 */

char *_strcat(char *dest, char *src)
{
	char *result =  NULL;
	int dest_len = _strlen(dest);
	int src_len = _strlen(src);

	result = malloc(sizeof(*result) * (dest_len + src_len + 1));
	_strcpy(dest, result);
	_strcpy(src, result + dest_len);
	result[dest_len + src_len] = '\0';
	return (result);
}

/**
 * _strspn - gets the length of  prefix substring.
 * @input_str: string searched.
 * @accept: string used.
 *
 * Return: num of bytes in the initial segment of 5 which are part of accept.
 */
int _strspn(char *input_str, char *accept)
{
	int i = 0;
	int match = 0;

	while (input_str[i] != '\0')
	{
		if (_strchr(accept, input_str[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 * _strcspn - computes segment of input_str that comprises
 *		characters not found in reject
 * @input_str: string to be searched
 * @reject: string to be used
 * Return: index at which a char in input_str exists in reject
 */
int _strcspn(char *input_str, char *reject)
{
	int len = 0, i;

	for (i = 0; input_str[i] != '\0'; i++)
	{
		if (_strchr(reject, input_str[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 * _strchr - locates a charater within a string
 * @str: string searched
 * @character: character to be checked
 *
 * Return: pointer to the first occurrence of character in string
 */
char *_strchr(char *str, char character)
{
	int i = 0;

	for (; str[i] != character && str[i] != '\0'; i++)
		;
	if (str[i] == character)
		return (str + i);
	else
		return (NULL);
}
