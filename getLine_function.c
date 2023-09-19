#include "shell.h"

/**
 * bufferInput - buffers chained commands from the input
 * @info: parameter structure
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: Number of bytes read
 */

ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t bufferLength = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, blockCtrlC);
#if USE_GETLINE
		bytesRead = getline(buffer, &bufferLength, stdin);
#else
		bytesRead = customGetline(info, buffer, &bufferLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->lineCountFlag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->histCount++);
			{
				*length = bytesRead;
				info->cmdBuffer = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * getInput - gets a line of input without newline
 * @info: parameter structure
 *
 * Return: Number of bytes read
 */

ssize_t getInput(info_t *info)
{
	static char *cmdBuffer;
	static size_t currentIndex, nextIndex, bufferLength;
	ssize_t bytesRead = 0;
	char **cmdBufferPointer = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &cmdBuffer, &bufferLength);
	if (bytesRead == -1)
		return (-1);
	if (bufferLength)
	{
		nextIndex = currentIndex;
		ptr = cmdBuffer + currentIndex;

		checkChain(info, cmdBuffer, &nextIndex, currentIndex, bufferLength);
		while (nextIndex < bufferLength)
		{
			if (isChain(info, cmdBuffer, &nextIndex))
				break;
			nextIndex++;
		}

		currentIndex = nextIndex + 1;
		if (currentIndex >= bufferLength)
		{
			currentIndex = bufferlength = 0
			info->cmdBufferType = CMD_NORM;
		}

		*cmdBufferPointer = ptr;
		return (customStrlen(ptr));
	}

	*cmdBufferPointer = cmdBuffer;
	return (bytesRead);
}

/**
 * readBuffer - reads from a buffer
 * @info: parameter structure
 * @buffer: buffer
 * @currentIndex: size
 *
 * Return: Number of bytes read
 */

ssize_t readBuffer(info_t *info, char *buffer, size_t *currentIndex)
{
	ssize_t bytesRead = 0;

	if (*currentIndex)
		return (0);
	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*currentIndex = bytesRead;
	return (bytesRead);
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: Number of bytes read
 */

int customGetline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t currentIndex, bufferLength;
	size_t k;
	ssize_t bytesRead = 0, totalBytesRead = 0;
	char *p = NULL, *newP = NULL, *c;

	p = *ptr;
	if (p && length)
		totalBytesRead = *length;
	if (currentIndex == bufferLength)
		currentIndex = bufferLength = 0;

	bytesRead = readBuffer(info, buffer, &bufferLength);
	if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
		return (-1);

	c = customStringFindCharacter(buffer + currentIndex, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : bufferLength;
	newP = customRealloc(p, totalBytesRead, totalBytesRead ?
			totalBytesRead + k : k + 1);
	if (!newP)
		return (p ? free(p), -1 : -1);

	if (totalBytesRead)
		customStringConcatenate(newP, buffer + currentIndex,
				k - currentIndex);
	else
		customStringCopy(newP, buffer + currentIndex, k - currentIndex + 1);

	totalBytesRead += k - currentIndex;
	currentIndex = k;
	p = newP;

	if (length)
		*length = totalBytesRead;
	*ptr = p;
	return (totalBytesRead);
}

/**
 * blockCtrlC - blocks Ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */

void blockCtrlC(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
