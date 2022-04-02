#include "../include/wrappers.h"

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

int Connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	int	res = connect(socket, address, address_len);
	if (res == -1) {
		perror("connect failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

int Inet_pton(int af, const char *restrict src, void *restrict dst) {
	int	res = inet_pton(af, src, dst);
	if (res == 0) {
		fprintf(stderr,
				"inet_pton failed: the address is not parseable"
				"in the specified address family\n");
		exit(EXIT_FAILURE);
	} else if (res == -1) {
		perror("inet_pton failed");
		exit(EXIT_FAILURE);
	}
	return res;
}