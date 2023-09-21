#include "shell.h"

/**
 * is_chain - Test if the current char in the buffer is a chain delimiter
 * @info: The parameter struct
 * @buf: The character bufferure
 * @p: Address of the current position in buff
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t r = *p;

	if (buf[r] == '|' && buf[r + 1] == '|')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[r] == '&' && buf[r + 1] == '&')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[r] == ';')
		/* Found the end of this command */
	{
		buf[r] = 0;
		/* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = r;
	return (1);
}

/**
 * check_chain - Check whether we should continue chaining based on last status
 * @info: The parameter structure
 * @buf: The character buff
 * @p: Address of the current position in buff
 * @i: Starting position in buff
 * @len: Length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t r = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			r = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			r = len;
		}
	}

	*p = r;
}

/**
 * replace_alias - Replace an alias in the tokenized string
 * @info: The parameter structurre
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
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
 * replace_vars - Replace variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(info->status,
							10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[n], "$$"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(getpid(),
							10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			replace_string(&(info->argv[n]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[n], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replace a string with a new one
 * @old: Address of the old string
 * @new: The new string
 *
 * Return: if replaced 1, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
