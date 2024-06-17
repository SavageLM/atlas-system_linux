#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

/**
 * main - entry to the function
 * @argc: number of arguments
 * @argv: array of args
 * Return: 0 on success
*/
int main(int argc, const char *argv)
{
	int client_fd;
	struct sockaddr_in server_add;

	if (argc < 3)
		printf("Usage: %s <host> <port>\n", argv[0]), exit(EXIT_FAILURE);
	
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	
	server_add.sin_family = AF_INET;
	server_add.sin_port = htons(atoi(argv[2]));

	if (connect(client_fd, (struct sockaddr *) &server_add, 
				sizeof(server_add)) < 0)
		printf("Failed to Connect\n");
	printf("Big Brother is in your walls now...\n");
	close(client_fd);
}
