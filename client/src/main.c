#include "../include/main.h"
#include "../include/wrappers.h"

void check_args(int argc, char *argv[], t_client *client) {
	if (argc == 1) {
		client->server_port = DEFAULT_PORT;
		client->server_ip = DEFAULT_IP;
		client->file_name = "send.txt"
	} else if (argc == 4) {
		client->server_ip = agrv[1];
		int port = atoi(argv[2]);
		if (0 < port && port < 65536) {
			client->server_port = port;
		} else {
			fprintf(stderr, "Wrong port number!\n");
			fprintf(stderr, USAGE);
			exit(EXIT_FAILURE);
		}
		if (0 == access(argv[3], R_OK)) {
			client->file_name = argv[3];
		} else {
			perror("access failed");
			fprintf(stderr, USAGE);
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}
}

void init_client(t_client *client) {
	client->fd = Socket(AF_INET, SOCK_STREAM, 0);
	client->address.sin_family = AF_INET;
	client->address.sin_port = htons(client->server_port);
	Inet_pton(AF_INET, client->server_ip, &client->address.sin_addr);
}

// TODO proper loop around write
void send_file(t_client *client) { // or just use sendfile()
	int file_fd = open(client->file_name, O_RDONLY); // protect
	char buf[BUF_SIZE] = {0};
	int n_read = 0;
	while ((n_read = read(file_fd, buf, sizeof buf))) { // FIXME errors
		if (n_read == -1) {
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		write(client->fd, buf, n_read); // protect
	}
	close(file_fd);
}

int main(int argc, char *argv[]) {
	t_client client = {0};
	check_args(argc, argv, &client);
	init_client(&client);

	Connect(client.fd, (struct sockaddr *) &client.address, sizeof client.address);

	send_file(&client);

	close(client.fd);
	return (0);
}