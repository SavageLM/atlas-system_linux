#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif
#include <netdb.h>

/**
 * main - entry to the function
 * @argc: number of arguments
 * @argv: array of args
 * Return: 0 on success
*/
int main(int argc, const char **argv)
{
	int client_fd;
	/* struct sockaddr_in server_add; */
	struct hostent *host;
	struct addrinfo hints = {0}, *addrs, *tmp = NULL;

	if (argc < 3)
		printf("Usage: %s <host> <port>\n", argv[0]), exit(EXIT_FAILURE);

	host = gethostbyname(argv[1]);
	if (host == NULL)
		perror("host not found"), exit(EXIT_FAILURE);
	hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(argv[1], argv[2], &hints, &addrs) != 0)
		perror("Failed to get address info"), exit(EXIT_FAILURE);
	for (tmp = addrs; tmp != NULL; tmp = tmp->ai_next)
	{
		client_fd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
	if (client_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	if (connect(client_fd, tmp->ai_addr, tmp->ai_addrlen) < 0)
		perror("Failed to Connect\n"), exit(EXIT_FAILURE);
	printf("Big Brother is in your walls now...\n");
	close(client_fd);
	}
	freeaddrinfo(addrs);
	return (0);
}
