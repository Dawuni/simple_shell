#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a structure that maps a command name to a function
 *
 *@command_name: name of a command
 *@func: function that executes the command
 */
typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **command_tokens;
extern char *input_line;
extern char **environ;
extern char *program_name;
extern int exit_status;

/*partners*/
char **tokenizer(char *input_str, char *delimiter)
void print_string(char *str_to_print, int output_stream)
void remove_newline(char *str_to_modify)
void copy_string(char *source_str, char *destination_str)
int string_length(char *str_to_measure)

/*partners1*/
int _strcmp(char *str1, char *str2)
char *_strcat(char *dest, char *src)
int _strspn(char *input_str, char *accept)
int _strcspn(char *input_str, char *reject)
char *_strchr(char *str, char character)

/*partners2*/
char *_strtok_r(char *input_string, char *delimiter, char **save_ptr)
int _atoi(char *str)
void *_realloc(void *memory_block, unsigned int current_size,
		unsigned int desired_size)
void ctrl_c_handler(int signal_number)
void remove_comment(char *input_string)

/*built-in*/
void env(char **args __attribute__((unused)))
void quit(char **args)

/*main*/
void initializer(char **cmd_tokens, int command_type)
void non_interactive(void)

/*utilities*/
int parse_command(char *command_str)
void execute_command(char **tokenized_command, int command_type)
char *check_path(char *command_str)
void (*get_func(char *command_str))(char **)
char *_getenv(char *variable_name)

#endif /*SHELL_H*/
