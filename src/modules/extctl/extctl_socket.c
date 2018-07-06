/*
 * extctl_socket_client.c
 *
 *  Created on: Jun 26, 2018
 *      Author: lidq
 */
#include "extctl_socket.h"

int _socket_id = -1;

#ifdef __USE_SOCKET

static struct sockaddr_un servaddr;

static int make_socket_non_blocking(int sfd);

static void client_exception(void);

int client_start()
{
	printf("[extctl] client start.\n");
//	for (int i = 0; i < 32; i++)
//	{
//		signal(i, (void (*)(int)) &client_exception);
//	}
//	signal(SIGPIPE, (void (*)(int)) &client_exception);

	printf("[extctl] client init.\n");
//创建套接字
	_socket_id = socket(PF_UNIX, SOCK_STREAM, 0);
	if (_socket_id == -1)
	{
		printf("[extctl] %s\n", strerror(errno));
		return -1;
	}

	if (make_socket_non_blocking(_socket_id) < 0)
	{
		printf("[extctl] make noblock error\n");
		return -1;
	}

	printf("[extctl] inet_pton\n");
	//IP地址和端口
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = PF_UNIX;
	strcpy(servaddr.sun_path, UNIX_DOMAIN);

	printf("[extctl] connect host\n");
	//连接到服务器
	int conn = connect(_socket_id, (struct sockaddr*) &servaddr, sizeof(servaddr));
	if (conn < 0)
	{
		printf("[extctl] %s\n", strerror(errno));
		pthread_detach(pthread_self());
		return -1;
	}

	return 0;
}

int make_socket_non_blocking(int sfd)
{
	int flags, s;

	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1)
	{
		printf("[extctl] fcntl error\n");
		return -1;
	}

	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1)
	{
		printf("[extctl] fcntl error\n");
		return -1;
	}

	return 0;
}

void client_exception()
{
	close(_socket_id);
	_socket_id = -1;
	exit(0);
}

#endif
