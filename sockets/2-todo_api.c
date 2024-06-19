#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE "HTTP/1.1 200 OK\r\n\r\n"
void query_parser(char *query);

/**
 * main - entry to the function
 * Return: 0 on success
*/
int main(void)
{
	int socket_fd, new_con;
	size_t bytes = 0;
	char buffer[4096], sent[32] = MESSAGE;
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
			query_parser(buffer);
		}
		send(new_con, sent, sizeof(sent), 0);
		close(new_con);
	}
	return (0);
}

/**
 * query_parser - pares an http query
 * @query: query string to parse
*/
void query_parser(char *query)
{
	int i = 0, flag = 0;
	char *token = NULL, *headers[16] = {0}, key[50], val[50];

	do {
		token = strsep(&query, "\r\n");
		if (token)
			headers[i++] = token, flag = 1;
	} while (token && flag--);

	for (i = 1; headers[i]; i++)
	{
		if (sscanf(headers[i],"%[^:]:%s", key, val) > 0)
			printf("Header: \"%s\" -> \"%s\"\n", key, val), fflush(stdout);
	}
}
