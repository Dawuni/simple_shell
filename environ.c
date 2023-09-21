#include "shell.h"


/**
 * _myenv - Prints the current environ.
 * @info: Structure containing pot arguments. Used to maintain
 *         constant func prototype.
 *
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment var.
 * @info: Struct containing poten arguments. Used to maintain
 * @name: Environ variable name.
 *
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes new environ var or modifies an existing one.
 * @info: Structure containing poten arguments. Used to maintain
 *		a constant func prototype.
 *
 *
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Struct containing potent arguments. Used to maintain
 *		a constant func prototype.
 *
 *
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		_unsetenv(info, info->argv[n]);

	return (0);
}

/**
 * populate_env_list - Populates the environ linked list.
 * @info: Struct containing poten arguments. Used to maintain
 *         a constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	info->env = node;
	return (0);
}
