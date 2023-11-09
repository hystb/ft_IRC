# include <global.hpp>

Client::Client(const std::string& nickname, int socket, Server& server) : _nickname(nickname), _socketFd(socket), _passwordUnlocked(0), _userConnected(0), _server(server), _username("\0"), _toDisconnect(0) {}

Client::~Client(void) {}

std::string	Client::getNickname(void) const {
	return _nickname;
}

std::string	Client::getUsername(void) const {
	return _username;
}

std::string	Client::getRealname(void) const {
	return _realname;
}

std::string&	Client::getBuffer(void) {
	return _buffer;
}

int		Client::getSocket(void) const {
	return _socketFd;
}

Server&	Client::getServer(void) const {
	return _server;
}

bool	Client::isPassWordUnlocked(void) const {
	return _passwordUnlocked;
}

bool	Client::isConnected(void) const {
	return _userConnected;
}

bool	Client::isToDisconnect(void) const {
	return _toDisconnect;
}

void	Client::setDisconnection(bool value) {
	_toDisconnect = value;
}

void	Client::setUsername(std::string& username){
	_username = username;
}

void	Client::setPassordUnlocked(bool value) {
	_passwordUnlocked = value;
}

void	Client::setUserConnected(bool value) {
	_userConnected = value;
}

void	Client::setNickname(std::string& name) {
	_nickname = name;
}

void	Client::setRealname(std::string name) {
	_realname = name;
}


void 	Client::sendMessage(std::string message) const 
{
	if (send(_socketFd, message.c_str(), message.length(), 0) < 0)
		std::cout << "Failed to send a message to the client !" << std::endl;	
}

void	Client::doLogin(void)
{
	if (isPassWordUnlocked() && getUsername() != "\0" && getNickname() != "undefined")
	{
		setUserConnected(1);
		RPL_WELCOME(*this);
		RPL_YOURHOST(*this);
		RPL_MYINFO(*this);
		RPL_ISUPPORT(*this);
		RPL_MOTDSTART(*this);
		RPL_MOTD(*this, "wow incroyable");
		RPL_ENDOFMOTD(*this);
	}
}

/* this functions will broadcast all others clients that are in the same channels that the target client */
void Client::broadcastFromClient(std::map<std::string, Channel*>& channels, Client* targetClient, std::string content)
{
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		Channel* actual = it->second;
		std::map<Client*, bool> users = actual->getClients();

		for (std::map<Client*, bool>::iterator jt = users.begin(); jt != users.end(); jt++)
		{
			Client* client = jt->first;

			if (client != targetClient)
				client->sendMessage(content);
		}
	}
}