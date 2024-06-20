#include "sockets.h"

todo_t *list = NULL;

/**
 * main - entry to the function
 * Return: 0 on success
*/
int main(void)
{
	int socket_fd, new_con;
	size_t bytes = 0;
	char buffer[4096];
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	address.sin_family = AF_INET, address.sin_port = htons(8080);
	address.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	if (listen(socket_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);
	while (1)
	{
		new_con = accept(socket_fd, (struct sockaddr *)&address, &addrlen);
		if (new_con < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		printf("Client connected: %s\n", inet_ntoa(address.sin_addr));
		bytes = recv(new_con, buffer, 4096, 0);
		if (bytes > 0)
		{
			printf("Raw request: \"%s\"\n", buffer), fflush(stdout);
			process_req(buffer, new_con);
		}
		close(new_con);
	}
	return (0);
}

/**
 * process_req - processes a request
 * @request: request to process
 * @fd: file descriptor for socket connection
 */
void process_req(char *request, int fd)
{
	char meth[50], path[50];

	printf("Entering process_req\n");
	sscanf(request, "%s %s", meth, path);
	if (strcmp(meth, "POST") != 0 && strcmp(meth, "GET") != 0)
		{
			send(fd, STAT_404, sizeof(STAT_404), 0);
			return;
		}
	if (strcmp(path, "/todos") != 0)
	{
		send(fd, STAT_404, strlen(STAT_404), 0);
		return;
	}
	head_parser(request, fd);
}

/**
 * head_parser - pares an http query
 * @query: query string to parse
 * @fd: file descriptor for socket connection
 */
void head_parser(char *query, int fd)
{
	int i = 0, flag = 0;
	char *token = NULL, *lines[16] = {0}, *body = NULL, key[50], val[50];

	printf("Entering head_parser\n");
	do {
		token = strsep(&query, "\r\n");
		if (token)
			lines[i++] = token, flag = 1;
	} while (token && flag--);

	body = lines[i - 1];
	for (i = 1; lines[i]; i++)
	{
		sscanf(lines[i],"%[^:]:%s", key, val);
		if (strcmp(key, "Content-Length") == 0)
			flag = 1;
	}
	if (!flag)
	{
		send(fd, STAT_411, strlen(STAT_411), 0);
		return;
	}
	printf("%s\n", body);
	task_parser(body, fd);
}

/**
 * task_parser - pares an http query
 * @query: query string to parse
 * @fd: file descriptor for socket connection
*/
void task_parser(char *query, int fd)
{
	int i = 0, flag = 0, flag_k = 1, flag_d = 1;
	char *token = NULL, *key_vals[16] = {0}, key[50], val[50], *title, *desc;

	printf("Entering task_parser\n");
	do {
		token = strsep(&query, "&");
		if (token && token[0])
			key_vals[i++] = token, flag = 1;
	} while (token && flag--);

	for (i = 0; key_vals[i]; i++)
	{
		sscanf(key_vals[i],"%[^=]=%s", key, val);
		if (strcmp(key, "title") == 0)
			title = strdup(val), flag_k = 0;
		else if (strcmp(key, "description") == 0)
			desc = strdup(val), flag_d = 0;
	}
	if (flag_k && flag_d)
	{
		send(fd, STAT_422, strlen(STAT_422), 0);
		return;
	}
	printf("title:%s\ndesc:%s\n",title, desc);
	add_todo(desc, title, fd);
}

/**
 * add_todo - FUnction to add to the todo list
 * @desc: description of task
 * @title: title of task
 * @fd: file descriptor for socket connection
 */
void add_todo(char *desc, char *title, int fd)
{
	static size_t id;
	int len = 0;
	char buffer[1024];
	todo_t *new_todo = NULL, *tmp;

	printf("Entering add_todo\n");
	new_todo = calloc(1, sizeof(todo_t));
	if (!new_todo)
		return;
	new_todo->id = id;
	new_todo->title = strdup(title);
	new_todo->description = strdup(desc);
	new_todo->next = NULL;
	id++;
	if (!list)
		list = new_todo;
	tmp = list;
	for (; tmp; tmp = tmp->next)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new_todo;
				break;
			}
		}
		sprintf(buffer, "{\"id\":%lu,\"title\":\"%s\",\"description\":\"%s\"}",
				id, title, desc);
		len = strlen(buffer);
		printf("%s\n", buffer), fflush(stdout);
		dprintf(fd, "%s", STAT_201), dprintf(fd,"Content-Length: %d\r\n", len);
		dprintf(fd, "Content-Type: application/json");
		dprintf(fd, "%s", buffer);
}
