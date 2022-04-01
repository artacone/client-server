#include "../include/main.h"
#include "../include/wrappers.h"

int main() {
	int	server_fd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address = {0}, client_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	Bind(server_fd, (struct sockaddr *)&server_address, sizeof server_address);

	Listen(server_fd, LISTEN_BL);

	socklen_t	address_len = sizeof server_address;
	int client_fd = Accept(server_fd, (struct sockaddr *)&client_address, &address_len);
	ssize_t	nread;
	char buf[256];
	nread = read(client_fd, buf, 256);
	if (nread == -1) {
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if (nread == 0) {
		printf("END OF FILE occurred\n");
	}
	write(STDOUT_FILENO, buf, nread); // protect
	write(client_fd, buf, nread); // protect

	sleep(1);
	close(client_fd);
	close(server_fd);
	return (0);
}