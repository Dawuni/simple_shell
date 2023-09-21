#include "shell.h"


/**
 * get_environ - Returns a cpy of the env vars as a string array.
 * @info: Structs containing poten arguments. Used to maintain
 *		a constant func prototype.
 *
 *
 * Return: 0 always
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environ variable.
 * @info: Structs containing poten arguments. Used to maintain
 *	a constant func of prototype.
 * @var: The name of the environ variable to remove.
 *
 *
 * Return: 1 if variable was deleted,  otherwise 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t q = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), q);
			q = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		q++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environ var or modifies an existing one.
 * @info: Structs containing poten arguments. Used to maintain
 *		a constant func prototype.
 * @var: The name of the environ variable.
 * @value: The value to set for the environ variable.
 *
 *
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
