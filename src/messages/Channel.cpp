/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:44 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:55:45 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <Channel.hpp>

Channel::Channel(const std::string& name, Client *client) : _name(name) {
	addClient(client, 1);
	_inviteOnlyMode = 0;
	_topicRestriction = 0;// A VERIFIER
	_limit = MAX_CLIENTS;
	// std::cout << "Channel: constructor called" << std::endl;
	_channel_nb += 1;//to deleted
}

Channel::~Channel(void) {}

// clients map
void Channel::addClient(Client *client, bool isOperator) {
	sendMessage(":" + client->getNickname() + " JOIN " + this->_name);
	_clients.insert(std::pair<Client*, bool>(client, isOperator));
}

void Channel::removeClient(Client *client) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first == client) {
			_clients.erase(it->first);
		break;
		}
	}
}

void Channel::removeClient(const std::string &nickname) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first->getNickname() == nickname) {
			_clients.erase(it->first);
		break;
		}
	}
}

void Channel::setOperator(Client *client) {
	_clients[client] = 1;
}

void Channel::unsetOperator(Client *client) {
	_clients[client] = 0;
}

// invited vector
void Channel::addInvited(Client *client) {
	_invited.push_back(client);
}

void Channel::removeInvited(const std::string& nickname) {
	for (std::vector<Client*>::iterator it = _invited.begin(); it != _invited.end(); ++it) {
		if ((*it)->getNickname() == nickname) {
			_invited.erase(it);
		break;
		}
	}
}

// setters
void	Channel::setPassword(const std::string& password) { _password = password; }
void	Channel::setLimit(unsigned long limit) { _limit = limit; }
void	Channel::setInviteOnlyMode(void) { _inviteOnlyMode = 1; }
void	Channel::unsetInviteOnlyMode(void) { _inviteOnlyMode = 0; }
void	Channel::setTopicRestriction(void) { _topicRestriction = 1; }
void	Channel::unsetTopicRestriction(void) { _topicRestriction = 0; }
void	Channel::setTopic(const std::string& topic) { _topic = topic; }

// getters
std::string		Channel::getName(void) const { return _name; }
std::string		Channel::getTopic(void) const { return _topic; }
std::string		Channel::getPassword(void) const { return _password; }
unsigned long	Channel::getLimit(void) const { return _limit; }
std::map<Client*, bool>& Channel::getClients(void) { return (_clients); }
bool			Channel::isInviteOnlyMode(void) const { return _inviteOnlyMode; }
bool 			Channel::isTopicRestriction(void) const { return _topicRestriction; }

void addMode(std::string& modes, bool condition, char modeChar) {
    modes += (condition ? '+' : '-');
    modes += modeChar;
	if (modeChar != 'l')
		modes += ' ';
}

std::string	Channel::getModes(void) const {
    std::string modes;

    addMode(modes, isInviteOnlyMode(), 'i');
    addMode(modes, isTopicRestriction(), 't');
    addMode(modes, !_password.empty(), 'k');
    addMode(modes, _limit != MAX_CLIENTS, 'l');

    return modes;
}

bool Channel::isMember(Client *client) {
	std::map<Client*, bool>::iterator it = _clients.find(client);
	if (it != _clients.end())
		return true;
	return false;
}

bool Channel::isMember(const std::string &nickname) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first->getNickname() == nickname)
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

bool Channel::isInvited(const std::string& nickname) {
	for (std::vector<Client*>::iterator it = _invited.begin(); it != _invited.end(); ++it) {
		if ((*it)->getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

// attributes
void	Channel::sendMessage(std::string message) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); it++)
		it->first->sendMessage(message);
}

std::string	Channel::listClients(void) {
	std::string message;

	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		const Client* client = it->first;
		bool isOperator = it->second;
		if (isOperator == true)
			message += "@";
		message += client->getNickname();
		message += " ";
	}
	return message;
}

void	Channel::sendMessageWithoutClient(std::string message, Client* without) {
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->first != without)
			it->first->sendMessage(message);
  }
}

void Channel::actualiseClientsList(void) {
	for (std::map<Client*, bool>::iterator it = getClients().begin(); it != getClients().end(); ++it) {
		const Client* client = it->first;
		RPL_NAMREPLY(*client, this);
		RPL_ENDOFNAMES(*client, this);
	}
}

void Channel::actualiseMode(const Client &target, char action, char symbol) {
	for (std::map<Client*, bool>::iterator it = getClients().begin(); it != getClients().end(); ++it) {
			const Client* client = it->first;
			if (symbol == 'o')
				LOG_MODE(this, *client, target, action, symbol);
			else if (symbol == 'k' && action == '+') {
				LOG_MODE3(this,  *client, action, symbol, _password);
			}
			else if (symbol == 'l')
				LOG_MODE4(this,  *client, action, symbol, _limit);
			else //t i -k{
			{
				LOG_MODE2(this,  *client, action, symbol);
			}
	}
}

// only for tests

void Channel::TestListInvited(void) {} //to do

void Channel::TestListClients() {
	std::cout << "BEGIN - Client list in channel " << getName() << std::endl;
	for (std::map<Client*, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		const Client* client = it->first;
		bool isOperator = it->second;
		std::cout << "Client: " << client->getNickname();
		if (isOperator)
			std::cout << " is Operator" << std::endl;
		else
			std::cout << " is Ordinary mortals" << std::endl;
	}
	std::cout << "END -" << std::endl;
}

int Channel::_channel_nb = 0;
