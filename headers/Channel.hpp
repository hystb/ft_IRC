#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <global.hpp>

class Client;

class Channel
{
	public:
		Channel(const std::string& name, Client *client);
		~Channel(void);

		// clients map
		void	addClient(Client *client, bool isOperator);
		void	removeClient(Client *client);
		void	removeClient(const std::string &nickname);
		void	setModerator(Client *client);
		
		// invited vector
		void	addInvited(Client *client);
		void	removeInvited(const std::string& nickname);
		
		// setters
		void	setPassword(const std::string& password);

		// getters
		std::string	getName(void) const;
		std::string	getPassword(void) const;
		std::string	getTopic(void) const;
		unsigned long getLimit(void) const;
		bool		isInviteOnlyMode(void);
		std::map<Client*, bool>& getClients(void);

		bool 	isMember(Client *client);
		bool 	isMember(const std::string &nickname);
		bool	isOperator(Client *client);
		bool	isInvited(const std::string& nickname);

		// attributes
		void	sendMessage(std::string message);
		void	sendMessageWithoutClient(std::string message, Client* without);


		std::string listClients(void);

		// only for tests
		void	TestListClients(void);
		void	TestListInvited(void);
		static int 				_channel_nb;

	private:
		std::string 			_name;
		std::string 			_topic;
		std::string				_password;
		unsigned long			_limit;
		bool					_inviteOnlyMode;
		std::vector<Client*>	_invited;
		std::map<Client*, bool>	_clients;
};

#endif
