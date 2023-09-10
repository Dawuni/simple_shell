#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */
void non_interactive(void)
{
	char **cmd_tokens = NULL;
	int command_index, command_type = 0;
	size_t buffer_size = 0;
	char *input_line = NULL;
	char **command_list = NULL;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&input_line, &buffer_size, stdin) != -1)
		{
			remove_newline(input_line);
			remove_comment(input_line);
			command_list = tokenizer(input_line, ";");
			for (command_index = 0; command_list[command_index] != NULL;
					command_index++)
			{
				cmd_tokens = tokenizer(command_list[command_index], " ");
				if (cmd_tokens[0] == NULL)
				{
					free(cmd_tokens);
					break;
				}
				command_type = parse_command(cmd_tokens[0]);
				initializer(cmd_tokens, command_type);
				free(cmd_tokens);
			}
			free(command_list);
		}
		free(input_line);
		exit(status);
	}
}
