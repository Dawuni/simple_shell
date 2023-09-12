#include "shell.h"

char **command_tokens = NULL;
char *input_line = NULL;
char *program_name = NULL;
int exit_status = 0;

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * Applies the functions in utilities and partners
 * Implements EOF
 * Prints error on failure
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char **current_tokens = NULL;
	int command_index, command_type = 0;
	size_t line_buffer_size = 0;

	signal(SIGINT, ctrl_c_handler);
	program_name = argv[0];

	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&input_line, &line_buffer_size, stdin) == -1)
		{
			free(input_line);
			exit(exit_status);
		}
		remove_newline(input_line);
		remove_comment(input_line);
		command_tokens = tokenizer(input_line, ";");

		for (command_index = 0; command_tokens[command_index] != NULL;
				command_index++)
		{
			current_tokens = tokenizer(command_tokens
					[command_index], " ");
			if (current_tokens[0] == NULL)
			{
				free(current_tokens);
				break;
			}
			command_type = parse_command(current_tokens[0]);
			initializer(current_tokens, command_type);
			free(current_tokens);
		}
		free(command_tokens);
	}
	free(input_line);

	return (exit_status);
}
