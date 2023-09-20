#include "shell.h"

/**
 * isexecutable - checks if a file is an executable command
 * @info: the information struct
 * @filePath: path to the file
 *
 * Return: 1 if it's executable, 0 otherwise
 */
int isexecutable(info_t *info, char *filePath)
{
	struct stat fileInfo;

	(void)info;
	if (!filePath || stat(filePath, &fileInfo))
		return (0);

	if (fileInfo.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copySubstring - duplicates characters from a string
 * @inputStr: the input string
 * @start: starting index
 * @end: ending index
 *
 * Return: a pointer to a new buffer containing the copied substring
 */
char *copySubstring(char *inputStr, int start, int end)
{
	static char buffer[1024];
	int bufferIndex = 0, i = start;

	for (i = start; i < end; i++)
	{
		if (inputStr[i] != ':')
			buffer[bufferIndex++] = inputStr[i];
	}
	buffer[bufferIndex] = '\0';
	return (buffer);
}

/**
 * findExecutablePath - finds the full path of a command in the PATH string
 * @info: the information struct
 * @pathString: the PATH string
 * @command: the command to find
 *
 * Return: the full path of the command if found, or NULL
 */
char *findExecutablePath(info_t *info, char *pathString, char *command)
{
	int i = 0, currPos = 0;
	char *path;

	if (!pathString)
	return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (isExecutable(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			path = copySubstring(pathString, currPos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (isExecutable(info, path))
				return (path);
			if (!pathString[i])
				break;
			currPos = i;
		}
		i++;
	}
	return (NULL);
}
