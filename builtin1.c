#include "shell.h"


/**
 * _myhistory - Displays the hist list, one cmd per line, preceded
 *		by line num, starting at 0.
 * @info: Struct containing potential arguments. Used to maintain
 *		constant func prototype.
 *
 *
 * Return: Always returns 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias.
 * @info: Parameter structure.
 * @str: The str alias.
 *
 *
 * Return: Always returns 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int rett;

	p = _strchr(str, '=');
	if (!p)
	return (1);
	c = *p;
	*p = 0;
	rett = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (rett);
}

/**
 * set_alias - Sets an alias to a given string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 *
 * Return: Always returns 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
	return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias of a string.
 * @node: The alias node.
 *
 *
 * Return: Always returns 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Structure containing pot arguments. Used to maintain
 *        constant func prototype.
 *
 *
 * Return: Always returns 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
		set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv
						[i], '='));
	}

	return (0);
}
