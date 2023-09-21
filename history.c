#include "shell.h"


/**
 * get_history_file - Retrieves hist file path.
 * @info: Structs containing potent arguments. Used to maintain
 *		a constant func prototype.
 *
 *
 * Return: Allocated string containing the hist file path.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Creates a file or inscribe to an existing history file.
 * @info: Structs containing poten arguments. Used to maintain
 *		a constant function prototype.
 *
 *
 * Return: On success 1, else -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t file_d;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_d == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_d);
		_putfd('\n', file_d);
	}
	_putfd(BUF_FLUSH, file_d);
	close(file_d);
	return (1);
}

/**
 * read_history - Read history from file.
 * @info: Structs containing poten arguments. Used to maintain
 *        a constant func prototype.
 *
 *
 * Return: Num of hist entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int q, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (q = 0; q < fsize; q++)
		if (buf[q] == '\n')
		{
			buf[q] = 0;
			build_history_list(info, buf + last, linecount++);
			last = q + 1;
		}
	if (last != q)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds entry to a hist linked list.
 * @info: Structs containing poten arguments. Used to maintain
 *		a constant func prototype.
 * @buf: The buffer containing the hist entry.
 * @linecount: The hist line count.
 *
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renum the hist linked list after changes.
 * @info: Structs containing poten arguments. Used to maintain
 *		a constant func prototype.
 *
 *
 * Return: The new hist count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int q = 0;

	while (node)
	{
		node->num = q++;
		node = node->next;
	}
	return (info->histcount = q);
}
