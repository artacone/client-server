#ifndef MAIN_H
# define MAIN_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define USAGE			"Usage:\n./server.out [port_number dir_name]\n"
#define	DEFAULT_PORT	50000
#define	DEFAULT_DIR		"."
#define	LISTEN_BACKLOG	5
#define	BUF_SIZE		4096

typedef struct s_server {
	int					fd;
	struct sockaddr_in	address;
	char				*dir_name;
	unsigned			port;
} t_server;

#endif