#include "shell.h"


/**
 * strtow - Splits a str into words. Repeated delimiters are ignored.
 * @str: The input str
 * @d: The delimiter str
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int p, r, k, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (p = 0; str[p] != '\0'; p++)
		if (!is_delim(str[p], d) && (is_delim(str[p + 1], d) || !str
					[p + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, r = 0; r < numwords; r++)
	{
		while (is_delim(str[p], d))
			p++;
		k = 0;
		while (!is_delim(str[p + k], d) && str[p + k])
			k++;
		s[r] = malloc((k + 1) * sizeof(char));
		if (!s[r])
		{
			for (k = 0; k < r; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < k; t++)
			s[r][t] = str[p++];
		s[r][t] = 0;
	}
	s[r] = NULL;
	return (s);
}

/**
 * strtow2 - Splits a string into words using a specified delimiter
 * @str: The input string
 * @d: The delimiter
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int p, r, k, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (p = 0; str[p] != '\0'; p++)
		if ((str[p] != d && str[p + 1] == d) ||
				    (str[p] != d && !str[p + 1]) || str[p + 1]
					== d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, r = 0; r < numwords; r++)
	{
		while (str[p] == d && str[p] != d)
			p++;
		k = 0;
		while (str[p + k] != d && str[p + k] && str[p + k] != d)
			k++;
		s[r] = malloc((k + 1) * sizeof(char));
		if (!s[r])
		{
			for (k = 0; k < r; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < k; t++)
			s[r][t] = str[p++];
		s[r][t] = 0;
	}
	s[r] = NULL;
	return (s);
}
