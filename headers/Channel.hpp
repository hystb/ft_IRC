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

		// client map
		void addClient(Client *client, bool isModerator);
		void removeClient(const std::string& username);
		void listClients(void);
		void setModerator(Client *client);

		// invited vector
		void removeInvited(const std::string& username);
		void addInvited(Client *client);
		void listInvited(void);
		bool isInvited(const std::string& username);

		// getter
		std::string	getName(void) const;
		std::string	getPassword(void) const;
		std::string	getTopic(void) const;
		int			getLimit(void) const;

		// extra
		void	sendMessage(std::string message) const;

	private:
		std::string 			_name;
		std::string 			_topic;
		std::string				_password;
		int						_limit;
		std::vector<Client*>	_invited;
		std::map<Client*, bool>	_clients;

		Channel(void);
};

#endif
