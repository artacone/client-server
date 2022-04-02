#include "../include/main.h"
#include "../include/wrappers.h"

/**
 * Checks program's args and sets parameters of the connection accordingly.
 * If no args recieved sets default parameters.
 * If args are incorrect or of a wrong number outputs Usage to stderr.
 * @param argc number of arguments
 * @param argv program's arguments
 * @param client pointer to the client struct
 */
void check_args(int argc, char *argv[], t_client *client) {
	if (argc == 1) {
		client->server_port = DEFAULT_PORT;
		client->server_ip = DEFAULT_IP;
		client->file_name = "send.txt";
	} else if (argc == 4) {
		client->server_ip = argv[1];
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

// TODO not always just exit -- check actual errors
/**
 * Sends the file "client->file_name" to the server.
 * Note: it would have been better to use sendfile() system call,
 * but it's interface is platform-specific.
 * @param client pointer to the client struct
 */
void send_file(t_client *client) {
	int file_fd = open(client->file_name, O_RDONLY);
	if (file_fd == -1) {
		perror("open failed");
		close(client->fd);
		exit(EXIT_FAILURE);
	}
	char buf[BUF_SIZE] = {0};
	while (1) {
		int n_read = read(file_fd, buf, sizeof buf);
		if (n_read == 0) {
			break;
		}
		if (n_read == -1) {
			perror("read failed");
			close(client->fd);
			exit(EXIT_FAILURE);
		}
		char *p = buf;
		while (n_read > 0) {
			int n_written = write(client->fd, p, n_read);
			if (n_written == -1) {
				perror("write failed");
				close(client->fd);
				exit(EXIT_FAILURE);
			}
			n_read -= n_written;
			p += n_written;
		}
	}
	close(file_fd);
}

int main(int argc, char *argv[]) {
	t_client client = {0};
	check_args(argc, argv, &client);
	init_client(&client);

	Connect(client.fd,
			(struct sockaddr *) &client.address,
					sizeof client.address);

	send_file(&client);

	close(client.fd);
	return (0);
}