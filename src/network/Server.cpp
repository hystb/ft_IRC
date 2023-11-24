# include <global.hpp>

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
		std::cout << YELLOW << Server::getServerLog() << YELLOW << "Server is binded on " << BOLD << "INADDR_ANY" << RESET << YELLOW " !" << YELLOW << RESET << std::endl;
		std::cout << Server::getServerLog() << GRAY << "Server now listening on " << RESET << PURPLE << BOLD << ip << ":" << _port << RESET << std::endl;
		std::cout << Server::getServerLog() << GRAY << "The password is : " << RESET << PURPLE << _password << RESET << std::endl;
	}
}

void	Server::SetEnd(void){
	_end = true;
}

/* this function get a full entry in a std::string until it reach \r\n */
int Server::getRawEntry(Client* client)
{
	char 		c_buff[1024];
	std::string &buff = client->getBuffer();
	int 		i;
	int			value;

	i = 0;
	while (i < 1024)
		c_buff[i++] = 0;
	value = recv(client->getSocket(), c_buff, 1023, 0);
	if (value <= 0)
		return (-1);
	buff.append(c_buff);
	return (1);
}

int Server::extractEntry(std::string del, std::string& dest, Client* client)
{
	std::string &buff = client->getBuffer();
	
	dest.clear();
	if (client->isToDisconnect())
		return (0);
	if (buff.length() >= del.length() && buff.find(del) != std::string::npos)
	{
		int j = buff.find(del);
		std::string toAdd;

		toAdd.append(buff.substr(0, j + del.length()));
		toAdd.append("\0");
		dest.append(toAdd);

		buff = buff.substr(j + del.length(), buff.length());
		return (1);
	}
	return (0);
}

void Server::start(void) {
	struct sockaddr_in 	sockaddr_client;
	int					socket_client;
	int					poll_value;
	socklen_t 			addrlen_client = sizeof(_sockaddr);

	_clients_fd[0].fd = _fd_sock;
	_clients_fd[0].events = POLLIN;
	while (_end == false) {
		poll_value = poll(_clients_fd, _clients_nb + 1, -1);
		if (poll_value < 0)
			interrupt();
		if (_clients_fd[0].revents & POLLIN) {
			socket_client = accept(_fd_sock, (sockaddr *) &sockaddr_client, &addrlen_client);
			if (socket_client < 0)
				interrupt();
			if (_clients_nb < MAX_CLIENTS) { // mean that there is some place
				_clients_fd[_clients_nb + 1].fd = socket_client;
				_clients_fd[_clients_nb + 1].events = POLLIN;
				_clients_fd[_clients_nb + 1].revents = 0;
				_clients_nb++;
				_clients.insert(std::pair<int, Client*>(socket_client, new Client("undefined", socket_client, *this)));
				std::cout << Server::getServerLog() << GRAY << "A new client successfuly connected to the server, waiting for loggin ! (" << socket_client << ")" << std::endl;
			}
			else {  // here refuse the client cause server is full
				sendMessage(socket_client, "Sorry, the server is actually full !\n\0");
				close(socket_client);
			}
		}
		for (int i = 1; i < _clients_nb + 1; i++) // this is for the actual connected users !
		{
			if (_clients_fd[i].revents & POLLIN) // mean that there is data here from a client
			{
				Client*		client = _clients[_clients_fd[i].fd];
				std::string messageReceived = "";
				int			value;

				value = getRawEntry(client);
				if (value == -1)
					handleClientDeconnection(i, 1);
				else if (value == 0) 
					continue;
				else if (value == 1)
				{
					while (extractEntry("\r\n", messageReceived, client))
					{
						try {
							_commandHandler.handleCommand(messageReceived, client, _channels, _clients);
						} catch (std::exception &e){
							std::cout << "Error : " << e.what() << std::endl;
						}
						messageReceived.clear();
					}
					if (client->isToDisconnect())
						handleClientDeconnection(i, 0);
				}
			}
		}
	}
}

void Server::handleClientDeconnection(int index, int type)
{
	Client *client = _clients[_clients_fd[index].fd];

	if (type)
		Client::warnOthersLeaving(client, "Lost connection !", _channels);
	if (client->getNickname() != "undefined" && client->getUsername() != "\0")
	{
		std::cout << Server::getServerLog() << GREEN << BOLD << client->getNickname() << RESET << GRAY << " disconnected from the server (" << client->getSocket() << ")" << RESET << std::endl;
		for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
			if (it->second->isMember(client->getNickname()))
				it->second->removeClient(client);
		}
	}
	else
		std::cout << Server::getServerLog() << GRAY << "Unlogged client disconnected from the server (" << client->getSocket() << ")" << RESET << std::endl;
	_clients.erase(client->getSocket());
	close(client->getSocket());
    for (int i = index; i < _clients_nb; i++) {
        _clients_fd[i] = _clients_fd[i + 1];
    }
    _clients_nb--;
	delete client;
}

void Server::disconnectClient(int fd)
{
	int i = 0;

	while (i <=_clients_nb && _clients_fd[i].fd != fd)
		i++;
	handleClientDeconnection(i, 0);
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

void Server::sendMessage(int client, std::string message)
{
	if (send(client, message.c_str(), message.length(), 0) < 0)
		std::cout << "Failed to send a message to the client !" << std::endl;	
}

std::string Server::getServerLog(void) {
	std::stringstream ss;

	ss << BOLD << + "[SERVER] " << RESET;
	return (ss.str());
}

void	Server::manageSig(void)
{
	struct sigaction	sig;

	sig.sa_handler =  &Server::handleSignal;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		std::cerr << "Error, SIGINT not define" << std::endl;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		std::cerr << "Error, SIGQUIT not define" << std::endl;
}

void	Server::handleSignal(int sig)
{
	if (sig == SIGINT)
	{
		_end = true;			
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

Server::Server(uint16_t port, std::string password, CommandHandler &cmd, std::map<int, Client*> &clients) : _port(port), _password(password), _commandHandler(cmd), _clients(clients), _end(false) {
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