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
	// mettre le client la !

	void parse(void);

public:
	/* canonical form */
	~Command(void);

	/* constructor */
	Command(std::string input, Client *client, std::map<std::string, Channel*>& channels);

	/* getters */
	const std::string&			 		getInput(void) const;
	const std::string& 					getCommand(void) const;
	const std::vector<std::string>& 	getParameters(void) const;
	const std::string&					getContent(void) const;

	std::map<std::string, Channel*>&  	getChannels(void);
	Client* 							getClient(void);


	/* exceptions */
	class invalidException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Invalid command syntax !"); };
	};
};
#endif

void ERR_BADCHANNELKEY(const Client &client, const Channel *channel);
void ERR_CHANNELISFULL(const Client &client, const Channel *channel);
void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel);
void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel);
void ERR_NEEDMOREPARAMS(const Client &client, const Channel *channel, const std::string &command);
void ERR_NOSUCHCHANNEL(const Client &client, const Channel *channel);
void ERR_NOTONCHANNEL(const Client &client, const Channel *channel);
void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel);
void JOIN_MSG(const Client &client, const Channel *channel);
void RPL_ENDOFNAMES(const Client &client, const Channel *channel);
void RPL_NAMREPLY(const Client &client, const Channel *channel);
void RPL_TOPIC(const Client &client, const Channel *channel);


