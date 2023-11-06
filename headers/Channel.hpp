#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <global.hpp>

class Client;

class Channel
{
	public:
		Channel(const std::string& name) : _name(name) {}
		~Channel(void);
		Channel& operator=(const Channel &parent);
		Channel(const Channel &parent);

		// map
		void addClient(Client &client);
		void removeClient(const std::string& username);
		void listClients(void);

		// setter???

	private:
		Channel(void);
		std::string 			_name;
		std::map<Client, bool>	_clients;//0 or 1 if moderator
};

#endif
