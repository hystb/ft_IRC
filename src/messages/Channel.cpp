# include <global.hpp>

// canonical
Channel::Channel(void) {}

Channel::Channel(const std::string& name, const std::string& password, Client *client) : _name(name), _password(password) {
	addClient(client, 1);
}

Channel::Channel(const Channel &parent)
{
	(*this) = parent;
}

Channel& Channel::operator=(const Channel &parent)
{
	return (*this);
}

Channel::~Channel(void) {}

// map
void Channel::addClient(Client *client, bool isModerator) {
	sendMessage(":" + client->getUsername() + " JOIN #" + this->_name);//log
	_clients.insert(std::pair<Client*, bool>(client, isModerator));
}

void Channel::removeClient(const std::string& username) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ) {
		if (it->first->getUsername() == username)
			_clients.erase(it++);
		else
			++it;
	}
}

void Channel::listClients() {
	for (std::map<Client*, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		const Client* client = it->first;
		bool isModerator = it->second;
		std::cout << "Client: " << client->getNickname();
		if (isModerator)
			std::cout << " Moderator" << std::endl;
		else
			std::cout << " Ordinary mortals" << std::endl;
	}
}

void Channel::setModerator(Client *client) {
	_clients[client] = 1;
}

// getter
std::string	Channel::getName(void) const { return _name; }
std::string	Channel::getTopic(void) const { return _topic; }
std::string	Channel::getPassword(void) const { return _password; }

// extra
void	Channel::sendMessage(std::string message) const {}
