#include "../include/main.h"
#include "../include/wrappers.h"

int main() {
	int	client_fd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(SERVER_PORT);
	Inet_pton(AF_INET, SERVER_IP, &address.sin_addr);

	Connect(client_fd, (struct sockaddr *) &address, sizeof address);
	write(client_fd, "Hello!\n", 7); // protect
	char	buf[256];
	ssize_t	nread;
	nread = read(client_fd, buf, sizeof buf);
	if (nread == -1) {
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if (nread == 0) {
		printf("End Of File occurred\n");
	}
	write(STDOUT_FILENO, buf, nread); // protect
	close(client_fd);
	return (0);
}