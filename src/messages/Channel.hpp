#ifndef CHANNEL_HPP
#define CHANNEL_HPP

//#include <vector>
#include <map>
#include <iostream>
#include "Client.hpp"

class Channel
{
	public:
		// canonical
		Channel(const std::string& name);
		~Channel(void);
		Channel& operator=(Channel &parent);//const ?
		Channel(const Channel &parent);

		// map
		// void addClient(const Client &client);
		void addClient(const Client &client, bool isModerator);
		void removeClient(const std::string& username);
		void listClients(void);
		void setModerator(Client &client);

	private:
		Channel(void);
		std::string 			_name;
		std::map<Client, bool>	_clients;
};

#endif
