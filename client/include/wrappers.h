#ifndef WRAPPERS_H
# define WRAPPERS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>

int		Socket(int domain, int type, int protocol);
void	Bind(int socket, const struct sockaddr *address, socklen_t address_len);
void	Listen(int socket, int backlog);
int		Accept(int socket, struct sockaddr *address, socklen_t *address_len);
int		Connect(int socket, const struct sockaddr *address, socklen_t address_len);
int		Inet_pton(int af, const char *restrict src, void *restrict dst);

#endif
