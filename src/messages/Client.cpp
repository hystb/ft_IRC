#include "Client.hpp"

Client::Client(const std::string& username, int socket) : _username(username), _socketFd(socket), _passwordUnlocked(0), _userConnected(0) {}

Client::Client(const Client &parent)
{
	(*this) = parent;
}

Client& Client::operator=(const Client &parent)
{
	(void) parent;
	//do something here;
	return (*this);
}

Client::~Client(void) {}


std::string	Client::getUsername(void) const {
	return _username;
}

int		Client::getSocket(void) const {
	return _socketFd;
}

bool	Client::isPassWordUnlocked(void) const {
	return _passwordUnlocked;
}

bool	Client::isConnected(void) const {
	return _userConnected;
}

void 	Client::sendMessage(std::string message) const 
{
	if (send(_socketFd, message.c_str(), message.length(), 0) < 0)
		std::cout << "Failed to send a message to the client !" << std::endl;	
}