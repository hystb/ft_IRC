#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <global.hpp>

class Client;

class Channel
{
	public:
		// canonical
		Channel(const std::string& name, const std::string& password, Client *client);
		~Channel(void);
		Channel& operator=(const Channel &parent);//const ?
		Channel(const Channel &parent);

		// map
		// void addClient(const Client &client);
		void addClient(Client *client, bool isModerator);
		void removeClient(const std::string& username);
		void listClients(void);
		void setModerator(Client *client);

		// getter
		std::string	getName(void) const;
		std::string	getPassword(void) const;
		std::string	getTopic(void) const;

		// extra
		void	sendMessage(std::string message) const;

		/* getters */
		std::map<Client*, bool>& getClients(void);
	private:
		Channel(void);
		std::string 			_name;
		std::string 			_topic;
		std::string				_password;
		std::map<Client*, bool>	_clients;
};

#endif
