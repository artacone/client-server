#include "../include/main.h"
#include "../include/wrappers.h"

void init_client(t_client *client) {
	client->fd = Socket(AF_INET, SOCK_STREAM, 0);
	client->address.sin_family = AF_INET;
	client->address.sin_port = htons(SERVER_PORT);
	Inet_pton(AF_INET, SERVER_IP, &client->address.sin_addr);
}

// TODO proper loop around write
void send_file(int file_fd, t_client *client) { // or just use sendfile()
	char buf[BUF_SIZE] = {0};
	int n_read = 0;
	while ((n_read = read(file_fd, buf, sizeof buf))) { // FIXME errors
		if (n_read == -1) {
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		write(client->fd, buf, n_read); // protect
	}
}

int main() {
	t_client client = {0};
	init_client(&client);

	Connect(client.fd, (struct sockaddr *) &client.address, sizeof client.address);

	char *file_name = "send.txt";
	int file_fd = open(file_name, O_RDONLY); // protect

	send_file(file_fd, &client);

	close(file_fd);
	close(client.fd);
	return (0);
}