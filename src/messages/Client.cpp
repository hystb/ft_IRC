#include "Client.hpp"

Client::Client(const std::string& username, bool isModerator) : _username(username), _isModerator(isModerator) {}

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

bool	Client::getIsModerator(void) const {
	return _isModerator;
}
