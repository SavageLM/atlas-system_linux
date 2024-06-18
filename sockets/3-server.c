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
	int socket_fd, new_con;
	char buffer[1024];
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	address.sin_family = AF_INET;
	address.sin_port = htons(12345);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);

	printf("Big Brother Listening on Port 12345");
	if (listen(socket_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);

	new_con = accept(socket_fd, (struct sockaddr *)&address, &addrlen);
	if (new_con < 0)
		perror("accept failed"), exit(EXIT_FAILURE);
	printf("IP address is: %s\n", inet_ntoa(address.sin_addr));

	read(new_con, buffer, 1024 - 1);
	printf("%s\n", buffer);
	close(new_con), close (socket_fd);
	return (0);
}
