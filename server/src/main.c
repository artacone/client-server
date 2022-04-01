#include "../include/main.h"

int Socket(int domain, int type, int protocol) {
	int	res = socket(domain, type, protocol);
	if (res == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

void Bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	int	res = bind(socket, address, address_len);
	if (res == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void Listen(int socket, int backlog) {
	int	res = listen(socket, backlog);
	if (res == -1) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
}

int Accept(int socket, struct sockaddr *restrict address,
			socklen_t *restrict address_len) {
	int	res = accept(socket, address, address_len);
	if (res == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

int main() {
	int	server_fd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address = {0}, client_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	Bind(server_fd, (struct sockaddr *)&server_address, sizeof server_address);

	Listen(server_fd, 10);

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

//	close(client_fd);
//	close(server_fd);
	return (0);
}