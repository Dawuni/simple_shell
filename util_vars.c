#include "shell.h"

/**
 * isCommandChain - checks if the current character
 *	in the buffer is a command chain delimiter
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if it's a command chain delimiter, 0 otherwise
 */
int isCommandChain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->commandChainType = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->commandChainType = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->commandChainType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkCommandChain - checks whether to continue chaining
 *	based on the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkCommandChain(info_t *info, char *buf, size_t *p,
		size_t i, size_t len)
{
	size_t j = *p;

	if (info->commandChainType == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->commandChainType == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replaceAliases - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
					_strdup(convertNumber(info->status,
							10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
					_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
