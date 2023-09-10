#include "shell.h"

/**
 * tokenizer - store input in an array after tokenization
 * @input_str: The input string to be parsed.
 * @delimiter: the delimiter to be used must be a single charater string
 *
 * Return: tokens array
 */

char **tokenizer(char *input_str, char *delimiter)
{
	int num_token = 0;
	char **tokens = NULL;
	char *current_token = NULL;
	char *tokenize_state = NULL;


	current_token = _strtok_r(input_str, delimiter, &tokenize_state);

	while (current_token != NULL)
	{
		tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
				sizeof(*tokens) * (num_tokens + 1));
		tokens[num_tokens] = current_token;
		current_token = _strtok_r(NULL, delimiter, &tokenize_state);
		num_tokens++;
	}

	tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
			sizeof(*tokens) * (num_tokens + 1));
	tokens[num_tokens] = NULL;

	return (tokens);
}


/**
 * print_string - Output a string to standard output (stdout)
 * @str_to_print: printed string
 * @output_stream: print out the stream
 *
 * Return: void
 */

void print_string(char *str_to_print, int output_stream)
{
	int i = 0;

	for (; str_to_print[i] != '\0'; i++)
		write(output_stream, &str_to_print[i], 1);
}

/**
 * remove_newline - remove newline characters from a string
 * @str_to_modify: to be used string
 *
 * Return: void
 */

void remove_newline(char *str_to_modify)
{
	int i = 0;

	while (str_to_modify[i] != '\0')
	{
		if (str_to_modify[i] == '\n')
			break;
		i++;
	}
	 str_to_modify[i] = '\0';
}

/**
 * copy_string - copies a string to a different buffer
 * @source_str: copy from source
 * @destination_str: copy to destination
 *
 * Return: void
 */

void copy_string(char *source_str, char *destination_str)
{
	int i = 0;

	for (; source_str[i] != '\0'; i++)
		destination_str[i] = source_str[i];
	destination_str[i] = '\0';
}

/**
 * string_length - calculate the length of a string
 * @str_to_measure: to be counted string
 *
 * Return: the length of a string
 */

int string_length(char *str_to_measure)
{
	int len = 0;

	if (str_to_measure == NULL)
		return (len);
	for (; str_to_measure[len] != '\0'; len++)
		;
	return (len);
}
