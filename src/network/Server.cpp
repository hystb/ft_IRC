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

void Server::prepare(void) {
	_sockaddr.sin_port = htons(_port);
	_sockaddr.sin_family = PF_INET;
	_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // revoir ça ! ou IN_ADDR_ANY

	_fd_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (_fd_sock == -1)
		throw (initSocketException());
	if (bind(_fd_sock, (sockaddr *)&_sockaddr, sizeof(_sockaddr)) == -1)
		throw (initBindException());
	if (listen(_fd_sock, 128) == -1)
		throw (Server::initListenException());
	std::cout << "Server now listening on " << std::endl;
}

void Server::start(void) {
	socklen_t addrlen = sizeof(_sockaddr);

	while (1) {
		if (accept(_fd_sock, (sockaddr *) &_sockaddr, &addrlen))
			std::cout << "dwadwa" << std::endl;
	}
}

Server::Server(int16_t port, std::string password) : _port(port), _password(password) {
	try {
		prepare();
		start();
	} catch (std::exception &e)
	{
		std::cout << "Fatal : Server failed to initialized !" << std::endl;
		std::cout << "-> " << e.what() << std::endl;
		throw (e);
	}
}
