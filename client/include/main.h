#ifndef MAIN_H
# define MAIN_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define USAGE			"Usage:\n./client.out [server_ip server_port file]\n"
#define	DEFAULT_PORT	50000
#define	DEFAULT_IP		"127.0.0.1"
#define	BUF_SIZE		4096

typedef struct s_client {
	int					fd;
	struct sockaddr_in	address;
	int					server_port;
	const char			*server_ip;
	const char			*file_name;
} t_client;

#endif