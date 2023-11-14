#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <global.hpp>

class Client;

class Channel
{
	public:
		// canonical
		Channel(const std::string& name, Client *client);
		~Channel(void);
		Channel& operator=(const Channel &parent);//const ?
		Channel(const Channel &parent);

		// client map
		void	addClient(Client *client, bool isOperator);
		void	removeClient(Client *client);
		void	setModerator(Client *client);
		void	listClients(void);// for test only
		bool 	isMember(Client *client);
		bool 	isMember(const std::string &clientName);
		bool	isOperator(Client *client);

		// invited vector
		void	addInvited(Client *client);
		void	removeInvited(const std::string& username);
		void	listInvited(void);//for test only
		bool	isInvited(const std::string& username);

		// getter
		std::string	getName(void) const;
		std::string	getPassword(void) const;
		std::string	getTopic(void) const;
		int			getLimit(void) const;
		static int 				_channel_nb;

		// setter
		void	setPassword(const std::string& password);

		// extra
		void	sendMessage(std::string message) const;

		/* getters */
		std::map<Client*, bool>& getClients(void);
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
