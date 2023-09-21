#include "shell.h"


/**
 * _strlen - Calculate the length of a string
 * @s: The string whose length to be checked
 *
 * Return: Integer length of the string
 */
int _strlen(char *x)
{
	int p = 0;

	if (!x)
		return (0);

	while (*x++)
		p++;
	return (p);
}

/**
 * _strcmp - Compare two strings lexicographically
 * @s1: The first string
 * @s2: The second string
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check if a string starts with a specified substring
 * @haystack: The string to search within
 * @needle: The substring to find at the beginning of haystack
 *
 * Return: Address of the next char in haystack after needle or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenate two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
