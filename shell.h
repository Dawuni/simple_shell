#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* shell_main.c */
int main(int argc, char **argv);

/* command.c */
int isExecutable(info_t *, char *);
char *copySubstring(char *, int, int);
char *findExecutablePath(info_t *, char *, char *);

/* getLine_function.c*/
ssize_t bufferInput(info_t *, char **, size_t *);
ssize_t getInput(info_t *info);
ssize_t readBuffer(info_t *, char *, size_t *);
int customGetline(info_t *, char **, size_t *);
void blockCtrlC(__attribute__((unused))int sigNum);

/* partner_1.c*/
int displayHelp(shellInfo_t *);
int changeDirectory(shellInfo_t *);
int exitShell(shellInfo_t *);

/* function.c  */
void customPrintError(char *);
int customPrintCharacter(char);
int customPrintToFileDescriptor(char, int );
int customPrintStringToFileDescriptor(char *, int);

/* string_pointer.c */
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcatenate(char *, char *);

/* string_ptr1.c */
char *copyString(char *, char *);
char *duplicateString(const char *);
void printString(char *);
int writeCharacter(char);

/* exits_function_1.c */
char *customStringCopy(char *, char *, int);
char *customStringConcatenate(char *, char *, int);
char *customStringFindCharacter(char *, char);

/* intial_tokenizer.c */
char **splitStringByDelim(char *, char *);
char **splitStringByChar(char *, char);

/* mem_realloc.c */
char *setMemory(char *, char, unsigned int);
void freeStringArray(char **);
void *resizeMemoryBlock(void *, unsigned int, unsigned int);

/* storage.c */
int freeAndNull(void **);

/* partner.c */
int Interactive_Mode(shellInfo_t *);
int isDelimiter(char, char *);
int isAlpha(int);
int convertStringToInteger(char *);

/* function_1.c */
int customAtoi(char *);
void printErrorMessage(info_t *, char *);
int customPrintInteger(int, int);
char *convertToBase(long int, int, int);
void removeFirstComment(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* partner_2.c */
int displayCommandHistory(shellData_t *);
int removeAlias(shellData_t *, char *);
int setAlias(shellData_t *, char *);
int printAlias(list_t  *);
int manageAlias(shellData_t  *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* int_getinfo.c */
void initializeInfo(info_t *);
void populateInfo(info_t *, char **);
void freeInfo(info_t *, int);

/* Env_1.c */
char *getEnvironmentVariable(shellInfo_t *, const char *);
int printCurrentEnvironment(shellInfo_t *);
int setEnvironmentVariable(shellInfo_t *);
int unsetEnvironmentVariable(shellInfo_t *);
int populateEnvironmentList(shellInfo_t *);

/* getenv_function.c */
char **copyEnvironment(info_t *);
int removeEnvironmentVariable(info_t *, char *);
int setEnvironmentVariable(info_t *, char *, char *);

/* past_hist.c */
char *getHistoryFile(info_t *info);
int writeHistoryToFile(info_t *info);
int readHistoryFromFile(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* helpers_1.c */
list_t *addNodeToFront(list_t **, const char *, int);
list_t *addNodeToEnd(list_t **, const char *, int);
size_t printListData(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* helpers.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t *, const char *, int);
size_t printListString(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
ssize_t get_node_index(list_t *, list_t *);

/* util_vars.c*/
int isCommandChain(info_t *, char *, size_t *);
void checkCommandChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAliases(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

/* program_loop.c */
int shellLoop(info_t *, char **);
int findBuiltin(info_t *);
void findCommand(info_t *);
void forkCommand(info_t *);

#endif

