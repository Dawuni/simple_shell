#include "shell.h"

/**
 * initializer - starts executing everything
 * @cmd_tokens: tokenized command
 * @command_type: parsed command type
 *
 * Return: void function
 */
void initializer(char **cmd_tokens, int command_type)
{
	pid_t child_pid;

	if (command_type == EXTERNAL_COMMAND || command_type == PATH_COMMAND)
	{
		child_pid = fork();
		if (child_pid == 0)
			execute_command(cmd_tokens, command_type);
		else
		{
			waitpid(child_pid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(cmd_tokens, command_type);
}
