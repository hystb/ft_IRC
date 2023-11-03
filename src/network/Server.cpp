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

/* this functions prepare the server to receive connections by creating the socket, bindind it and start listening ! */
void Server::prepare(void) {
	int opt = 1;
	socklen_t addrlen_serv = sizeof(_sockaddr);

	_sockaddr.sin_port = htons(_port);
	_sockaddr.sin_family = PF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_clients_nb = 0;

	_fd_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (_fd_sock == -1)
		throw (initSocketException());
	if (setsockopt(_fd_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0 || 
		bind(_fd_sock, (sockaddr *)&_sockaddr, sizeof(_sockaddr)) == -1 || 
		listen(_fd_sock, 128) == -1)
	{
		close(_fd_sock);
		throw (initException());
	}

	if (getsockname(_fd_sock, (sockaddr *) &_sockaddr, &addrlen_serv) == 0)
	{
		char ip[INET_ADDRSTRLEN];
		inet_ntop(PF_INET, &(_sockaddr.sin_addr), ip, INET_ADDRSTRLEN);
		std::cout << "Server now listening on " << ip << ":" << _port << std::endl;
		std::cout << "The password is : " << _password << std::endl;
	}
}
// /r/n pour finir message
void Server::start(void) {
	struct sockaddr_in 	sockaddr_client;
	int					socket_client;
	int					poll_value;
	socklen_t 			addrlen_client = sizeof(_sockaddr);

	_clients_fd[0].fd = _fd_sock;
	_clients_fd[0].events = POLLIN;
	while (1) {
		poll_value = poll(_clients_fd, _clients_nb + 1, -1);
		if (poll_value < 0)
			return ; // do something here
		if (_clients_fd[0].revents & POLLIN)
		{
			socket_client = accept(_fd_sock, (sockaddr *) &sockaddr_client, &addrlen_client);
			if (socket_client < 0)
				return ; // do something here
			if (_clients_nb < MAX_CLIENTS) // mean that there is some place
			{
				std::cout << "There is a new client with the socket number " << socket_client << std::endl;
				_clients_fd[_clients_nb + 1].fd = socket_client;
				_clients_fd[_clients_nb + 1].events = POLLIN;
				_clients_nb++;
				std::cout << "nombres de clients maintenant : " << _clients_nb << std::endl;
			}
			else // here refuse the client cause server is full
			{
				close(socket_client);
			}
		}
		for (int i = 1; i <= _clients_nb; i++)	
		{
			if (_clients_fd[i].revents & POLLIN) // mean that there is data here from a client
			{
				char buff[1234];
				read(_clients_fd[i].fd, buff, 1000);
				std::cout << "Le message recu du fd " << _clients_fd[i].fd << " :" << buff << std::endl;
			}
		}
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
