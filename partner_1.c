#include "shell.h"

/**
 * exitShell - exits the shell
 * @shellInfo: Structure containing potential arguments to maintain
 *	constant function of prototype.
 * Return: exits with a given exit status
 * (0) if shellInfo->args[0] != "exit"
 */

int exitShell(shellInfo_t *shellInfo)
{
	int exitStatus;

	if (shellInfo->args[1]) /* If there is an exit argument */
	{
		exitStatus = _customAtoi(shellInfo->args[1]);
		if (exitStatus == -1)
		{
			shellInfo->exitCode = 2;
			printError(shellInfo, "Illegal number: ");
			_eputs(shellInfo->args[1]);
			_eputchar('\n');
			return (1);
		}
		shellInfo->exitCode = _customAtoi(shellInfo->args[1]);
		return (-2);
	}
	shellInfo->exitCode = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the process
 * @shellInfo: Structure containing potential arguments to maintain
 *	constant function of prototype.
 * Return: Always 0
 *
 */

int changeDirectory(shellInfo_t *shellInfo)
{
	char *currentDirectory, *newDirectory, buffer[1024];
	int chdirResult;

	currentDirectory = getcwd(buffer, 1024);
	if (!currentDirectory)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!shellInfo->args[1])
	{
		newDirectory = _getenv(shellInfo, "HOME=");
		if (!newDirectory)
			chdirResult = /* TODO: what should this be? */
				chdir((newDirectory = _getenv(shellInfo, "PWD="))
						? newDirectory : "/");
		else
			chdirResult = chdir(newDirectory);
	}
	else if (_strcmp(shellInfo->args[1], "-") == 0)
	{
		if (!_getenv(shellInfo, "OLDPWD="))
		{
			_puts(currentDirectory);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shellInfo, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((newDirectory = _getenv(shellInfo, "OLDPWD=")) ?
					newDirectory : "/");
	}
	else
		chdirResult = chdir(shellInfo->args[1]);
	if (chdirResult == -1)
	{
		printError(shellInfo, "can't cd to ");
		_eputs(shellInfo->args[1]), _eputchar('\n');
	}
	else
	{
		_setenv(shellInfo, "OLDPWD", _getenv(shellInfo, "PWD="));
		_setenv(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * displayHelp - displays help information for the shell
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int displayHelp(shellInfo_t *shellInfo)
{
	char **argumentsArray;

	argumentsArray = shellInfo->args;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentsArray); /* Temporary unused argument workaround */
	return (0);
}
