#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE "HTTP/1.1 200 OK\r\n\r\n"

/**
 * main - entry to the function
 * Return: 0 on success
*/
int main(void)
{
	int socket_fd, new_con;
	size_t bytes = 0;
	char buffer[4096], meth[50], path[50], sent[32] = MESSAGE;
	char key1[50], val1[50], key2[50], val2[10], no_use[50];
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
			sscanf(buffer, "%s %[^?]? %[^=]= %[^&]& %[^=]= %[^&]& %s",
				   meth, path, key1, val1, key2, val2, no_use);
			printf("Path: %s\nQuery: \"%s\" -> \"%s\"\n", path, key1, val1);
			printf("Query: \"%s\" -> \"%s\"\n",  key2, val2);
		}
		send(new_con, sent, sizeof(sent), 0);
		close(new_con);
	}
	return (0);
}
