#include "shell.h"

/**
 * getHistoryFile - Returns the path to the history file.
 * @info: The parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */

char *getHistoryFile(info_t *info)
{
	char *homeDir, *historyFile;

	homeDir = _getenv(info, "HOME=");
	if (!homeDir)
		return (NULL);

	historyFile = malloc(sizeof(char) * (_strlen(homeDir) +
				_strlen(HIST_FILE) + 2));
	if (!historyFile)
		return (NULL);

	historyFile[0] = '\0';
	_strcpy(historyFile, homeDir);
	_strcat(historyFile, "/");
	_strcat(historyFile, HIST_FILE);

	return (historyFile);
}

/**
 * writeHistoryToFile - Writes the command history to a file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */

int writeHistoryToFile(info_t *info)
{
	ssize_t fileDescriptor;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fileDescriptor == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsToFileDescriptor(node->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}

	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * readHistoryFromFile - Reads command history from a file.
 * @info: The parameter struct.
 *
 * Return: histcount on success, 0 otherwise.
 */

int readHistoryFromFile(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fileDescriptor, readLength, fileSize = 0;
	struct stat fileStat;
	char *buffer = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fileDescriptor = open(filename, O_RDONLY);
	free(filename);

	if (fileDescriptor == -1)
		return (0);

	if (!fstat(fileDescriptor, &fileStat))
		fileSize = fileStat.st_size;

	if (fileSize < 2)
		return (0);

	buffer = malloc(sizeof(char) * (fileSize + 1));

	if (!buffer)
		return (0);

	readLength = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = '\0';

	if (readLength <= 0)
		return (free(buffer), 0);

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			buildHistoryList(info, buffer + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		buildHistoryList(info, buffer + last, linecount++);

	free(buffer);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - Adds an entry to the history linked list.
 * @info: The parameter struct.
 * @buffer: The command buffer.
 * @linecount: The history line count.
 *
 * Return: Always 0.
 */

int buildHistoryList(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	addNodeEnd(&node, buffer, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @info: The parameter struct.
 *
 * Return: The new histcount.
 */

int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
