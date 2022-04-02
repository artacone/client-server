#include "../include/main.h"
#include "../include/wrappers.h"

void init_server(t_server *server) {
	server->fd = Socket(AF_INET, SOCK_STREAM, 0);

	server->address.sin_family = AF_INET;
	server->address.sin_port = htons(SERVER_PORT);
	Bind(server->fd, (struct sockaddr *)&server->address, sizeof server->address);
	Listen(server->fd, LISTEN_BL);
}

void receive_file(int client_fd) {
	char *file_name = "recv.txt";
	char buf[BUF_SIZE] = {0};
	int file_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	int n_read = 0;
	while ((n_read = read(client_fd, buf, sizeof buf))) { // protect
		if (n_read == -1) {
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		write(file_fd, buf, n_read); // protect
	}
	close(file_fd);
}

int main() {
	t_server server = {0};
	init_server(&server);
	struct sockaddr_in address = {0};
	socklen_t address_len = sizeof address;
	while (1) {
		int client_fd = Accept(server.fd, (struct sockaddr *)&address, &address_len);

		int pid = fork(); // protect

		if (pid == 0) {
			close(server.fd);

			/* PROCESSING */
			receive_file(client_fd);
			exit(EXIT_SUCCESS);
		} else {
			close(client_fd);
		}
	}

	close(server.fd);
	return (0);
}