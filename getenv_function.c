#include "shell.h"

/**
 * copyEnvironment - returns a copy of the environment as a string array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: A copy of the environment as a string array.
 */

char **copyEnvironment(info_t *info)
{
	if (!info->environment || info->envChanged)
	{
		info->environment = listToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environment);
}

/**
 * removeEnvironmentVariable - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: The name of the environment variable to remove.
 * Return: 1 on deletion, 0 otherwise.
 */

int removeEnvironmentVariable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = startsWith(node->str, variable);
		if (p && *p == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env),
					index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initializes a new environment variable or
 *		modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * Return: Always 0.
 */

int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buf = malloc(customStrlen(variable) + customStrlen(value) + 2);
	if (!buf)
		return (1);
	customStringCopy(buf, variable);
	customStringConcatenate(buf, "=");
	customStringConcatenate(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}
