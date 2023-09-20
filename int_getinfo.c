#include "shell.h"

/**
 * initializeInfo - Initializes the info_t struct.
 * @info: The address of the info_t struct.
 */

void initializeInfo(info_t *info)
{
	info->arguments = NULL;
	info->argumentVector = NULL;
	info->path = NULL;
	info->argumentCount = 0;
}

/**
 * populateInfo - Populates the info_t struct.
 * @info: The address of the info_t struct.
 * @argumentVector: The argument vector.
 */

void populateInfo(info_t *info, char **argumentVector)
{
	int i = 0;

	info->programName = argumentVector[0];
	if (info->arguments)
	{
		info->argumentVector = splitString(info->arguments, " \t");
		if (!info->argumentVector)
		{
			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argumentVector[0] = duplicateString
					(info->arguments);
				info->argumentVector[1] = NULL;
			}
		}
		for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
			;
		info->argumentCount = i;

		replaceAliases(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - Frees fields in the info_t struct.
 * @info: The address of the info_t struct.
 * @freeAll: True if freeing all fields.
 */

void freeInfo(info_t *info, int freeAll)
{
	freeStringArray(info->argumentVector);
	info->argumentVector = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->commandBuffer)
			free(info->arguments);
		freeList(&(info->environment));
		freeList(&(info->history));
		freeList(&(info->aliases));
		freeStringArray(info->environmentCopy);
		info->environmentCopy = NULL;
		freeBuffer((void **)info->commandBuffer);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		writeToStandardOutput(BUF_FLUSH);
	}
}
