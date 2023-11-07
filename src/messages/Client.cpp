# include <global.hpp>

Client::Client(const std::string& username, int socket, Server& server) : _username(username), _socketFd(socket), _passwordUnlocked(0), _userConnected(0), _server(server) {}

Client::~Client(void) {}


std::string	Client::getUsername(void) const {
	return _username;
}

std::string& Client::getBuffer(void) {
	return _buffer;
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

void Client::setPassordUnlocked(bool value) {
	_passwordUnlocked = value;
}

void Client::setUserConnected(bool value) {
	_userConnected = value;
}

Server& Client::getServer(void) const {
	return _server;
}

void 	Client::sendMessage(std::string message) const 
{
	if (send(_socketFd, message.c_str(), message.length(), 0) < 0)
		std::cout << "Failed to send a message to the client !" << std::endl;	
}