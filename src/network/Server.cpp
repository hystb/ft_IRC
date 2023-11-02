#include "Server.hpp"

Server::Server(void) { }

Server::Server(const Server &parent)
{
	(*this) = parent;
}

Server& Server::operator=(const Server &parent)
{
	(void) parent;
	return (*this);
}

Server::~Server(void) {}

void Server::setup(void) {
	fd_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (fd_sock == -1)
		throw (Server::initException());
	if (bind(fd_sock, (sockaddr *)&_sockaddr, sizeof(_sockaddr)) == -1)
		throw (Server::initException());
	if (listen(fd_sock, 5000) == -1)
		throw (Server::initException());
	
}

void dev(void)
{
	int fd_sock;
	struct sockaddr_in serverAddress;

	serverAddress.sin_family = PF_INET;
	serverAddress.sin_port = htons(3000);

	fd_sock = socket(PF_INET, SOCK_STREAM, 0);
	bind(fd_sock, (sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(fd_sock, 10);
	std::cout << fd_sock << std::endl;
}