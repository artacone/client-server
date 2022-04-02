#ifndef MAIN_H
# define MAIN_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // htons() inet_pton()

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define	SERVER_PORT	50000
#define	SERVER_IP	"127.0.0.1"

#define	BUF_SIZE	256

typedef struct s_client {
	int					fd;
	struct sockaddr_in	address;
} t_client;

#endif