#include "shell.h"


/**
 * input_buf - Buffers chained cmds from input.
 * @info: Parameter structures.
 * @buf: Address of buff.
 * @len: Address of len variables.
 *
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*len)
		/* If nothing left in the buf, fill it */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		c = getline(buf, &len_p, stdin);
#else
		c = _getline(info, buf, &len_p);
#endif
		if (c > 0)
		{
			if ((*buf)[c - 1] == '\n')
			{
				(*buf)[c - 1] = '\0';
				/* Remove trailing newline */
				c--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = c;
				info->cmd_buf = buf;
			}
		}
	}
	return (c);
}

/**
 * get_input - Gets line minus the newline character.
 * @info: Parameter structs.
 *
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t n, j, len;
	ssize_t c = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buf, &len);
	if (c == -1) /* EOF */
		return (-1);
	if (len) /* We have cmds left in the chain buffer */
	{
		j = n; /* Initialize new iterator to current buff position */
		p = buf + n; /* Get pointer for return */

		check_chain(info, buf, &j, n, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		n = j + 1; /* Increment past nulled ';' */
		if (n >= len) /* Reached the end of the buffer? */
		{
			n = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back ptr to the current cmd position */
		return (_strlen(p)); /* Return the len of the current cmd */
	}

	*buf_p = buf; /* Else, not a chain, pass back the buf from _getline() */
	return (c); /* Return the len of the buf from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter structure.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t c = 0;

	if (*i)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*i = c;
	return (c);
}

/**
 * _getline - Gets the next line of input from the STDIN.
 * @info: Parameter structures.
 * @ptr: Address of pointer to buff, preallocated or NULL.
 * @length: Size of preallocated pointer buff if not NULL.
 *
 *
 * Return: size.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t k;
	ssize_t t = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (m == len)
		m = len = 0;

	t = read_buf(info, buf, &len);
	if (t == -1 || (t == 0 && len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + m, k - m);
	else
		_strncpy(new_p, buf + m, k - m + 1);

	s += k - m;
	m = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks Ctrl-C in the list.
 * @sig_num: The signal num.
 *
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
