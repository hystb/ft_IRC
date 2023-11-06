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
		bind(_fd_sock, (sockaddr *) &_sockaddr, sizeof(_sockaddr)) == -1 || 
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

/* this function get a full entry in a std::string until it reach \r\n */
int Server::getRawEntry(std::string &buff, int fd, std::string del)
{
	char 	c_buff[1024];
	int 	i;
	int		value;

	while (true)
	{
		i = 0;
		while (i < 1024)
			c_buff[i++] = 0;
		value = recv(fd, c_buff, 1023, 0);
		if (value == -1)
			return (-2);
		if (value == 0)
			return (-1);
		buff.append(c_buff);		
		if (buff.compare(buff.length() - del.length(), del.length(), del) == 0)
		{
			buff.append("\0");
			return (0);
		}
	}
}

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
			interrupt();
		if (_clients_fd[0].revents & POLLIN) {
			socket_client = accept(_fd_sock, (sockaddr *) &sockaddr_client, &addrlen_client);
			if (socket_client < 0)
				interrupt();
			if (_clients_nb < MAX_CLIENTS) { // mean that there is some place
				std::cout << "There is a new client with the socket number " << socket_client << std::endl;
				_clients_fd[_clients_nb + 1].fd = socket_client;
				_clients_fd[_clients_nb + 1].events = POLLIN;
				_clients_nb++;
				_clients.insert(std::pair<int, Client>(socket_client, Client("undefined", 0)));
			}
			else {  // here refuse the client cause server is full
				sendMessage(socket_client, "Sorry, the server is actually full !\n\0");
				close(socket_client);
			}
		}

		for (int i = 1; i <= _clients_nb; i++) // this is for the actual connected users !
		{
			if (_clients_fd[i].revents & POLLIN) // mean that there is data here from a client
			{
				std::string messageReceived = "";
				int			value;

				value = getRawEntry(messageReceived, _clients_fd[i].fd, "\r\n");
				if (value == -1)
					handleClientDeconnection(i);
				else if (value == -2)
					interrupt();
				else
				{
					for (int j = 1; j <= _clients_nb; j++)
					{
						if (_clients_fd[j].fd != _clients_fd[i].fd)
							sendMessage(_clients_fd[j].fd, messageReceived);
					}

					// try {
					// 	_command_handler.handleCommand(_clients_fd[i].fd, messageReceived);
					// } catch (std::exception &e){
					// 	std::cout << "Error : " << e.what() << std::endl;
					// }
				}
			}
		}
	}
}

void Server::handleClientDeconnection(int index)
{
	std::cout << "[" << _clients_fd[index].fd << "]: " << "disconnected !" << std::endl;

	_clients.erase(_clients_fd[index].fd);
	close(_clients_fd[index].fd);

    for (int i = index; i < _clients_nb; i++) {
        _clients_fd[i] = _clients_fd[i + 1];
    }
    _clients_nb--;
}

void Server::closeFds(void)
{
	for (int i = 0; i <= _clients_nb; i++)
		close(_clients_fd[i].fd);
}

void Server::interrupt(void)
{
	closeFds();
	std::cout << "Something bad happened !" << std::endl;
	throw (crashException());
}

void Server::sendMessage(int client, std::string message) // a remplacer et a mettre dans les clients !
{
	if (send(client, message.c_str(), message.length(), 0) < 0)
		std::cout << "Failed to send a message to the client !" << std::endl;	
}

Server::Server(uint16_t port, std::string password) : _port(port), _password(password) {
	try {
		prepare();
	} catch (std::exception &e)
	{
		std::cout << "Fatal : Server failed to initialized !" << std::endl;
		std::cout << "-> " << e.what() << std::endl;
		throw (e);
	}
	start();
}
