# include <global.hpp>

Client::Client(const std::string& nickname, int socket, Server& server) : _nickname(nickname), _username("\0"), _socketFd(socket), _passwordUnlocked(0),  _toDisconnect(0), _userConnected(0), _server(server) {}
Client::~Client(void) {}

// getters
int				Client::getSocket(void) const {	return _socketFd; }
Server&			Client::getServer(void) const { return _server; }
std::string&	Client::getBuffer(void) { return _buffer; }
std::string		Client::getNickname(void) const { return _nickname; }
std::string		Client::getUsername(void) const { return _username; }
std::string		Client::getRealname(void) const { return _realname; }
std::string		Client::getClientID(const Client &client) { return (":" + client.getNickname() + "!" + client.getUsername() + "@localhost"); }

bool	Client::isPassWordUnlocked(void) const { return _passwordUnlocked; }
bool	Client::isConnected(void) const { return _userConnected; }
bool	Client::isToDisconnect(void) const { return _toDisconnect; }

// setters
void	Client::setDisconnection(bool value) { _toDisconnect = value; }
void	Client::setUsername(std::string& username){ _username = username; }
void	Client::setPassordUnlocked(bool value) { _passwordUnlocked = value; }
void	Client::setUserConnected(bool value) { _userConnected = value; }
void	Client::setNickname(std::string& nickname) { _nickname = nickname; }
void	Client::setRealname(std::string realname) { _realname = realname; }

// attributes
void 	Client::sendMessage(std::string message) const 
{
	std::string toSend = message + "\r\n";
	std::cout << Server::getServerLog() << GREEN << "➡️ " << message << RESET << GRAY << "(" << getSocket() << ")" << RESET << std::endl;
	
	if (send(_socketFd, toSend.c_str(), toSend.length(), 0) < 0)
		std::cout << Server::getServerLog() << RED << "Failed to send a message to the client" << RESET << std::endl;
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
		RPL_MOTD(*this, "La team rocket s'envole vers d'autres ciels !");
		RPL_MOTD(*this, "\t\t%%%%%%%%%%%%%%%%%%   ");
		RPL_MOTD(*this, "\t\t%%%%%%%%%%%%%%%%%%%% ");
		RPL_MOTD(*this, "\t\t%%%%%        %%%%%%% ");
		RPL_MOTD(*this, "\t\t%%%%%%%%%%%%%%%%%%   ");
		RPL_MOTD(*this, "\t\t%%%%%%%%%%%%%%%%     ");
		RPL_MOTD(*this, "\t\t%%%%%      %%%%%     ");
		RPL_MOTD(*this, "\t\t%%%%%       %%%%%%%  ");
		RPL_MOTD(*this, "\t\t%%%%%       %%%%%%%%%");
		RPL_ENDOFMOTD(*this);
		std::cout << Server::getServerLog() << GRAY << "Client " << RESET << YELLOW << BOLD << getUsername() << RESET << GRAY << " successfuly log into the server as " << GREEN << BOLD << getNickname() << RESET << GRAY << " (" << getSocket() << ")" << RESET << std::endl;  
	}
}

Client* Client::getClientFromNickname(std::map<int, Client*>& clients, std::string nickname) {
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}
