# include <global.hpp>

// canonical
Channel::Channel(void) {}

Channel::Channel(const std::string& name) {}

Channel::Channel(const Channel &parent)
{
	(*this) = parent;
}

Channel& Channel::operator=(const Channel &parent)//const ?
{
	if (this != &parent) {
		// for (std::map<Client, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		// 	parent.addClient(it->first, it->second);
		// 	// parent._clients.insert(std::pair<Client, bool>(it->first, it->second));
		// }
	}
	return (*this);
}

Channel::~Channel(void) {}

// map
// void Channel::addClient(const Client &client) {
// 	_clients.insert(std::pair<Client, bool>(client, 0));
// }

void Channel::addClient(Client *client, bool isModerator) {
	_clients.insert(std::pair<Client*, bool>(client, isModerator));
}

void Channel::removeClient(const std::string& username) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ) {
		if (it->first->getNickname() == username) {
			_clients.erase(it++);
		} else {
			++it;
		}
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
