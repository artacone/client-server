#include "../include/main.h"
#include "../include/wrappers.h"
#include <string.h>
#include <time.h>

/**
 * Checks program's args. Sets port and dir_name fields of the server struct.
 * If no args recieved, sets default parameters.
 * If args are incorrect or of a wrong number, outputs Usage to stderr.
 * @param argc number of arguments
 * @param argv program's arguments
 * @param server pointer to the client struct
 */
void check_args(int argc, char *argv[], t_server *server) {
	if (argc == 1) {
		server->port = DEFAULT_PORT;
		server->dir_name = DEFAULT_DIR;
	} else if (argc == 3) {
		int port = atoi(argv[1]);
		if (0 < port && port < 65536) {
			server->port = port;
		} else {
			fprintf(stderr, "Wrong port number!\n");
			fprintf(stderr, USAGE);
			exit(EXIT_FAILURE);
		}
		if (0 == access(argv[2], W_OK | X_OK)) {
			server->dir_name = argv[2];
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

void init_server(t_server *server) {
	server->fd = Socket(AF_INET, SOCK_STREAM, 0);

	server->address.sin_family = AF_INET;
	server->address.sin_port = htons(server->port);
	Bind(server->fd,
		 (struct sockaddr *)&server->address,
				 sizeof server->address);
	Listen(server->fd, LISTEN_BACKLOG);
}

void receive_file(int client_fd, char *dir_name) {
	char file_name[256] = {0};
	time_t seconds = time(NULL);
	snprintf(file_name, sizeof file_name, "%s/recv_%ld", dir_name, seconds);
	char buf[BUF_SIZE] = {0};
	int file_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file_fd == -1) {
		perror("open failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	int n_read = 0;
	while ((n_read = read(client_fd, buf, sizeof buf))) {
		if (n_read == -1) {
			perror("read failed");
			close(file_fd);
			remove(file_name);
			close(client_fd);
			exit(EXIT_FAILURE);
		}
		if (write(file_fd, buf, n_read) == -1) {
			perror("write failed");
			close(file_fd);
			remove(file_name);
			close(client_fd);
			exit(EXIT_FAILURE);
		}
	}
	close(file_fd);
}

int main(int argc, char *argv[]) {
	t_server server = {0};
	check_args(argc, argv, &server);
	init_server(&server);
	struct sockaddr_in address = {0};
	socklen_t address_len = sizeof address;
	while (1) {
		int client_fd = Accept(server.fd,
							   (struct sockaddr *)&address,
									   &address_len);
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork failed");
			break;
		}
		if (pid == 0) {
			close(server.fd);
			receive_file(client_fd, server.dir_name);
			exit(EXIT_SUCCESS);
		} else {
			close(client_fd);
		}
	}
	close(server.fd);
	return (0);
}