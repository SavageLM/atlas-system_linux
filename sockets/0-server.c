#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 * main - entry to the function
 * Return: 0 on success
*/
int main(void)
{
	int socket_fd;
	struct sockaddr_in address;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(12345);

	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);

	listen(socket_fd, 5);
}
