#include "shell.h"

/**
 * env - prints the current environment
 * @args: command entered (tokenized)
 *
 * Return: void
 */
void env(char **args __attribute__((unused)))
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		print(environ[index], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @args: command entered (tokenized)
 *
 * Return: void
 */
void quit(char **args)
{
	int num_args = 0, arg;

	for (; args[num_args] != NULL; num_args++)
		;
	if (num_args == 1)
	{
		free(args);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_args == 2)
	{
		arg = _atoi(args[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(args[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(args);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n",
				STDERR_FILENO)
}
