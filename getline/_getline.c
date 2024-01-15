#include "_getline.h"

/**
 * _getline - reads from file descriptor, line-by-line per call until end
 * @fd: input file descriptor, next line of content requested
 * Return: next line of file or NULL
*/

char *_getline(const int fd)
{
	static file_buf *list;
	file_buf *file = NULL;
	char *line = NULL;

	file = node_find(&list, fd);
	if (!file)
		return (NULL);
	line = next_line(file);
	if (!line)
		free(file->buffer), file->buffer = NULL;
	return (line);
}

/**
 * node_find - queries file list & returns node matching file descriptor
 * @list: pointer to first node of file list, if applicable
 * @fd: input file descriptor by which inv is queried
 * Return: pointer to file in inventory referenced by fd
*/

file_buf *node_find(file_buf **list, int fd)
{
	file_buf *tmp = *list;
	size_t found = 0;

	for (; tmp; tmp = tmp->next)
		if (tmp->fd == fd)
		{
			found = 1;
			return (tmp);
		}
	if (!found)
		tmp = add_file(list, fd);
	return (tmp);
}

/**
 * add_node - add file content & rel attributes as node to linked list
 * @list: pointer to first node of file list, if applicable
 * @fd: input file descriptor supplied as identifier for added node
 * Return: pointer to added node upon success, NULL otherwise
*/

file_buf *add_node(file_buf **list, int fd)
{
	file_buf *new = NULL, *file = *list;

	new = malloc(sizeof(file_buf));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buff_bytes = 0;
	new->pos = 0;
	new->flag = 0;
	if (!(*list))
		*list = new;
	else
		for (; file; file = file->next)
			if (!file->next)
			{
				file->next = new;
				break;
			}
	new->next = NULL;
	new->buffer = reader(fd);
	if (!(new->buffer))
	{
		free(new);
		return (NULL);
	}
	for (
		;
		new->buffer[new->buff_bytes] != '\0' &&
		new->buffer[new->buff_bytes + 1 != '\0'];
		new->buff_bytes++
	)
		;
	return (new);
}

/**
 * reader - read fd to collect all readable bytes from file into string
 * @fd: input file descriptor to be read
 * Return: null-terminated string, or NULL
*/

char *reader(int fd)
{
	char *buffer = NULL, *out = NULL, *tmp = NULL;
	ssize_t bytes_read = 0, size = 0;

	buffer = malloc(READ_SIZE);
	if (!buffer)
		return (NULL);
	out = malloc(READ_SIZE);
	if (!out)
		return (NULL);
	while ((bytes_read = read(fd, buffer, READ_SIZE)))
	{
		if (bytes_read == -1)
		{
			free(out), out = NULL;
			break;
		}
		tmp = realloc(out, size + bytes_read + 1);
		if (!tmp)
		{
			free(out), out = NULL;
			break;
		}
		out = tmp;
		memcpy(out + size, buffer, bytes_read);
		size += bytes_read;
		out[size] = '\0';
	}
	free(buffer);
	return (out);
}

/**
 * next_line - pull next line from buffer of node related to input file
 * @file: input file contents from which to extract next line
 * Return: next line from buffer of input file stream as null-terminated string
 *         upon success, NULL otherwise
*/

char *next_line(file_buf *file)
{
	size_t mark = file->pos, span = 0, end = file->buff_bytes;
	char *txt = file->buffer, *line = NULL;

	if ((mark < end || (end == 0 && txt[mark] == '\n')) && !file->flag)
	{
		for (
			;
			mark != end &&
			txt[mark] != '\n' &&
			txt[mark] != '\0';
			mark++, span++
		)
			;
		line = malloc(sizeof(char) * span + 1);
		if (!line)
			return (NULL);
		for (
			span = 0;
			file->pos < mark &&
			txt[file->pos] != '\n' &&
			txt[file->pos] != '\0';
			file->pos++, span++
		)
			line[span] = txt[file->pos];
		if (txt[file->pos] == '\0' || txt[file->pos] == '\n')
			file->pos++;
		line[span] = '\0';
		if (!end && !file->flag)
			file->flag = 1;
	}
	else
		return (NULL);
	return (line);
}