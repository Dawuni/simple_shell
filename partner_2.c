#include "shell.h"

/**
 * _strtok_r - tokenizes string
 * @input_string: tokenize the string
 * @delimiter: specify the delimiter to tokenize the string with
 * @save_ptr: use a pointer to keep track of the next token
 *
 * Return: the next available token
 */
char *_strtok_r(char *input_string, char *delimiter, char **save_ptr)
{
	char *token_end;

	if (input_string == NULL)
		input_string = *save_ptr;

	if (*input_string == '\0')
	{
		*save_ptr = input_string;
		return (NULL);
	}

	input_string += _strspn(input_string, delimiter);
	if (*input_string == '\0')
	{
		*save_ptr = input_string;
		return (NULL);
	}

	token_end = input_string + _strcspn(input_string, delimiter);
	if (*token_end == '\0')
	{
		*save_ptr = token_end;
		return (input_string);
	}

	*token_end = '\0';
	*save_ptr = token_end + 1;
	return (input_string);
}

/**
 * _atoi - convert a string to an integer
 * @str: to be changed string
 *
 * Return: the changed integer
 */
int _atoi(char *str)
{
	unsigned int result = 0;

	do {
		if (*str == '-')
			return (-1);
		else if ((*str < '0' || *str > '9') && *str != '\0')
			return (-1);
		else if (*str >= '0'  && *str <= '9')
			result = (result * 10) + (*str - '0');
		else if (result > 0)
			break;
	} while (*str++);
	return (result);
}

/**
 * _realloc - move a memory block to a new location
 * @memory_block: pointer to memory allocated with malloc previously
 * @current_size: memory_block size
 * @desired_size: allocate memory for the new size required
 *
 * Return: A pointer to the new memory block's address
 */
void *_realloc(void *memory_block, unsigned int current_size,
		unsigned int desired_size)
{
	void *temp_block;
	unsigned int i;

	if (memory_block == NULL)
	{
		temp_block = malloc(desired_size);
		return (temp_block);
	}
	else if (desired_size == current_size)
		return (memory_block);
	else if (desired_size == 0 && memory_block != NULL)
	{
		free(memory_block);
		return (NULL);
	}
	else
	{
		temp_block = malloc(desired_size);
		if (temp_block != NULL)
		{
			for (i = 0; i < min(current_size, desired_size); i++)
				*((char *)temp_block + i) = *((char *)memory_block + i);
			free(memory_block);
			return (temp_block);
		}
		else
			return (NULL);
	}
}

/**
 * ctrl_c_handler - handles the signal raised by CTRL-C
 * @signal_number: signal number
 *
 * Return: void
 */
void ctrl_c_handler(int signal_number)
{
	if (signal_number == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * remove_comment - removes/ignores everything after a '#' char
 * @input_string: input to be used
 *
 * Return: void
 */
void remove_comment(char *input_string)
{
	int i = 0;

	if (input_string[i] == '#')
		input_string[i] = '\0';
	while (input_string[i] != '\0')
	{
		if (input_string[i] == '#' && input_string[i - 1] == ' ')
			break;
		i++;
	}
	input_string[i] = '\0';
}
