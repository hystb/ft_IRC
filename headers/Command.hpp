#ifndef COMMAND_HPP
#define COMMAND_HPP

# include <global.hpp>

class Command
{
private:
	std::string 						_input;
	std::string 						_command;
	std::vector<std::string>			_parameters;
	std::string							_content;
	Client* 							_client;
	std::map<std::string, Channel*>&	_channels;
	std::map<int, Client*>&				_clients;

	// mettre le client la !

	void parse(void);

public:
	/* canonical form */
	~Command(void);

	/* constructor */
	Command(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*>& clients);

	/* getters */
	const std::string&			 		getInput(void) const;
	const std::string& 					getCommand(void) const;
	const std::vector<std::string>& 	getParameters(void) const;
	std::string							getContent(void) const;

	std::map<std::string, Channel*>&  	getChannels(void);
	std::map<int, Client*>&				getClients(void);
	Client* 							getClient(void);


	/* exceptions */
	class invalidException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Invalid command syntax !"); };
	};
};

void RPL_WELCOME(const Client &client);
void RPL_YOURHOST(const Client &client);
void RPL_CREATED(const Client &client);
void RPL_MYINFO(const Client &client);
void RPL_ISUPPORT(const Client &client);
void RPL_MOTDSTART(const Client &client);
void RPL_MOTD(const Client &client, std::string motd);
void RPL_ENDOFMOTD(const Client &client);



void ERR_ALREADYREGISTERED(const Client &client);
void ERR_NOTREGISTERED(const Client &client);
void ERR_NEEDMOREPARAMS(const Client &client, std::string commandName);
void ERR_NICKNAMEINUSE(const Client &client, std::string nick);
void ERR_NONICKNAMEGIVEN(const Client &client);
void ERR_ERRONEUSNICKNAME(const Client &client, std::string nick);
void ERR_PASSWDMISMATCH(const Client &client);

#endif