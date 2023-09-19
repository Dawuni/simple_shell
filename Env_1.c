#include "shell.h"

/**
 * printCurrentEnvironment - prints the current environment
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int printCurrentEnvironment(shellInfo_t *shellInfo)
{
	printStringList(shellInfo->currentEnvironment);
	return (0);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @shellInfo: Structure containing potential arguments.
 * @variableName: name of the environment variable
 *
 * Return: the value of the environment variable
 */

char *getEnvironmentVariable(shellInfo_t *shellInfo, const char *variableName)
{
	list_t *node = shellInfo->currentEnvironment;
	char *envVarValue;

	while (node)
	{
		envVarValue = startsWith(node->str, variableName);
		if (envVarValue && *envVarValue)
		return (envVarValue);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *		or modify an existing one
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0
 */

int setEnvironmentVariable(shellInfo_t *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnv(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0
 */

int unsetEnvironmentVariable(shellInfo_t *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		unsetEnv(shellInfo, shellInfo->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates the environment linked list
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0
 */

int populateEnvironmentList(shellInfo_t *shellInfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeToEnd(&node, environ[i], 0);
	shellInfo->currentEnvironment = node;
	return (0);
}
