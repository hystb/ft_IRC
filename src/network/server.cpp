#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

void dev(void)
{
	int fd_sock;
	struct sockaddr_in addr;

	fd_sock = socket(PF_INET, SOCK_STREAM, 0);
	std::cout << fd_sock << std::endl;
}