#include "Channel.hpp"

// canonical
Channel::Channel(void) {}

Channel::Channel(const std::string& name) {}

Channel::Channel(const Channel &parent)
{
	(*this) = parent;
}

Channel& Channel::operator=(const Channel &parent)
{
	(void) parent;
	//do something here;
	return (*this);
}

// map
void Channel::addClient(Client &client) {
	_clients.insert(std::pair<Client, bool>(client, 0));
}

void Channel::removeClient(const std::string& username) {
	for (std::map<Client, bool>::iterator it = _clients.begin(); it != _clients.end(); ) {
		if (it->first.getUsername() == username) {
			_clients.erase(it++);
		} else {
			++it;
		}
	}
}

void Channel::listClients() {
	for (std::map<Client, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		const Client& client = it->first;
		bool isModerator = it->second;
		std::cout << "Client: " << client.getUsername();
		if (isModerator)
			std::cout << " Moderator" << std::endl;
		else
			std::cout << " Ordinary mortals" << std::endl;
	}
}

void Channel::setModerator(Client &client) {
	_clients[client] = 1;
}
