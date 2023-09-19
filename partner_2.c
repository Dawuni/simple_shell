#include "shell.h"

/**
 * displayCommandHistory - displays the command history list, one command
 *	per line,preceded with line numbers, starting at 0.
 * @shellData: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 *  Return: Always 0
 */

int displayCommandHistory(shellData_t *shellData)
{
	printHistoryList(shellData->commandHistory);
	return (0);
}

/**
 * removeAlias - removes an alias from the alias list.
 * @shellData: Structure containing potential arguments.
 * @aliasName: the alias to remove
 *
 * Return: Always 0 on success, 1 on error
 */

int removeAlias(shellData_t *shellData, char *aliasName)
{
	char *equalSign, tempChar;
	int result;

	equalSign = _strchr(aliasName, '=');
	if (!equalSign)
		return (1);
	tempChar = *equalSign;
	*equalSign = '\0';
	result = deleteNodeAtIndex(&(shellData->aliasList),
			getNodeIndex(shellData->aliasList, nodeStartsWith
				(shellData->aliasList, aliasName, -1)));
	*equalSign = tempChar;
	return (result);
}

/**
 * setAlias - sets an alias to a string.
 * @shellData: Structure containing potential arguments.
 * @aliasString: the string alias to set
 *
 * Return: Always 0 on success, 1 on error
 */

int setAlias(shellData_t *shellData, char *aliasString)
{
	char *equalSign;

	equalSign = _strchr(aliasString, '=');
	if (!equalSign)
		return (1);
	if (!*++equalSign)
		return (removeAlias(shellData, aliasString));

	removeAlias(shellData, aliasString);
	return (addNodeToEnd(&(shellData->aliasList), aliasString, 0) == NULL);
}

/**
 * printAlias - prints an alias string.
 * @aliasNode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int printAlias(list_t *aliasNode)
{
	char *equalSignPos = NULL, *aliasName = NULL;

	if (aliasNode)
	{

		equalSignPos = _strchr(aliasNode->str, '=');
		for (aliasName = aliasNode->str; aliasName <= equalSignPos;
				aliasName++)
		_putchar(*aliasName);
		_putchar('\'');
		_puts(equalSignPos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - mimics the alias builtin (man alias)
 * @shellData: Structure containing potential arguments. Used to maintain
 *             constant function prototype.
 *  Return: Always 0
 */

int manageAlias(shellData_t *shellData)
{
	int i = 0;
	char *equalSignPos = NULL;
	list_t *aliasNode = NULL;

	if (shellData->argc == 1)
	{
		aliasNode = shellData->aliasList;
		while (aliasNode)
		{
			printAlias(aliasNode);
			aliasNode = aliasNode->next;
		}
		return (0);
	}
	for (i = 1; shellData->argv[i]; i++)
	{
		equalSignPos = _strchr(shellData->argv[i], '=');
		if (equalSignPos)
			setAlias(shellData, shellData->argv[i]);
		else
			printAlias(nodeStartsWith(shellData->aliasList,
				shellData->argv[i], '='));
	}

	return (0);
}
