#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <global.hpp>

class Client;

class Channel
{
	public:
		// canonical
		Channel(const std::string& name);
		~Channel(void);
		Channel& operator=(const Channel &parent);//const ?
		Channel(const Channel &parent);

		// map
		// void addClient(const Client &client);
		void addClient(Client *client, bool isModerator);
		void removeClient(const std::string& username);
		void listClients(void);
		void setModerator(Client *client);

	private:
		Channel(void);
		std::string 			_name;
		std::map<Client*, bool>	_clients;
};

#endif
