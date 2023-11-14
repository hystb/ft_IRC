# include <global.hpp>

int Channel::_channel_nb = 0;

// canonical
Channel::Channel(void) {}

Channel::Channel(const std::string& name, Client *client) : _name(name) {
	_channel_nb += 1;
	addClient(client, 1);
	std::cout << "Channel: constructor called" << std::endl;
}

Channel::~Channel(void) {}

// client map
void Channel::addClient(Client *client, bool isOperator) {
	sendMessage(":" + client->getUsername() + " JOIN #" + this->_name);
	_clients.insert(std::pair<Client*, bool>(client, isOperator));
}

void Channel::removeClient(Client *client) {
	for (std::map<Client*, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ) {
		if (it->first == client) {
			_clients.erase(it);
		break;
		}
	}
}

void Channel::setModerator(Client *client) {
	_clients[client] = 1;
}

bool Channel::isMember(Client *client) {
	std::map<Client*, bool>::iterator it = _clients.find(client);
	if (it != _clients.end())
		return true;
return false;
}

bool Channel::isMember(const std::string &clientName) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first->getUsername() == clientName)
			return true;
	}
	return false;
}

bool Channel::isOperator(Client *client) {
	std::map<Client*, bool>::iterator it = _clients.find(client);
	if (it == _clients.end())
		return false;
	if (it->second)
		return true;
	return false;
}

void Channel::listClients() {
	for (std::map<Client*, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		const Client* client = it->first;
		bool isOperator = it->second;
		std::cout << "Client: " << client->getNickname();
		if (isOperator)
			std::cout << " Moderator" << std::endl;
		else
			std::cout << " Ordinary mortals" << std::endl;
	}
}

// invited vector
void Channel::addInvited(Client *client) {
	_invited.push_back(client);
}

void Channel::removeInvited(const std::string& username) {
	for (std::vector<Client*>::const_iterator it = _invited.begin(); it != _invited.end(); ++it) {
		if ((*it)->getUsername() == username) {
			_invited.erase(it);
			break;
		}
	}
}

bool Channel::isInvited(const std::string& username) {
	for (std::vector<Client*>::const_iterator it = _invited.begin(); it != _invited.end(); ++it) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}

void Channel::listInvited(void) {} //to do

// getter
std::string	Channel::getName(void) const { return _name; }
std::string	Channel::getTopic(void) const { return _topic; }
std::string	Channel::getPassword(void) const { return _password; }
int			Channel::getLimit(void) const { return _limit; }

// setter
void	Channel::setPassword(const std::string& password) {
	_password = password;
}

// extra
void	Channel::sendMessage(std::string message) const {}


std::map<Client*, bool>& Channel::getClients(void) {
	return (_clients);
}
