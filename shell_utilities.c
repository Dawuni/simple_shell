#include "shell.h"

/**
 * parse_command - determines type of command
 * @command_str: the command to be parsed
 *
 * Return: constant representing type of command
 */
int parse_command(char *command_str)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; command_str[i] != '\0'; i++)
	{
		if (command_str[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	path = check_path(command_str);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}
	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on the type
 * @tokenized_command: tokenized form of a command
 * @command_type: type of command
 *
 * Return: void
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*command_function)(char **);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		command_function = get_func(tokenized_command[0]);
		command_function(tokenized_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - checks if a command is found in the Path
 * @command_str: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *command_str)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command_str);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - retrieves function based on command given and mapping
 * @command_str: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command_str))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command_str, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @variable_name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *variable_name)
{
	char **my_environ;
	char *pair_pointer;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_pointer = *my_environ, name_cpy = variable_name;
			*pair_pointer == *name_cpy; pair_pointer++, name_cpy++)
		{
			if (*pair_pointer == '=')
				break;
		}
		if ((*pair_pointer == '=') && (*name_cpy == '\0'))
			return (pair_pointer + 1);

	}
	return (NULL);
}
