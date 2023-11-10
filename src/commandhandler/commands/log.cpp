# include <global.hpp>

void RPL_TOPIC(const Channel *channel, const Client &client) {
	// channel->sendMessage(client.getUsername() + " " + channel->getName() + " :" + channel->getTopic());
}

void RPL_NAMREPLY(const Channel *channel, const Client &client) {//to do
	// channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :" + channel->getTopic());
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}

void RPL_ENDOFNAMES(const Channel *channel, const Client &client) {
	// channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :End of /NAMES list");
	//"<client> <channel> :End of /NAMES list"
}

void ERR_NEEDMOREPARAMS(const Channel *channel, const Client &client, std::string &command) {
	// channel->sendMessage(client.getUsername() + " " + command +" :Not enough parameters");
	//"<client> <command> :Not enough parameters"
}

void ERR_NOSUCHCHANNEL(std::string &channel, const Client &client) {
	// channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :No such channel");
	//"<client> <channel> :No such channel"
}

void ERR_BADCHANNELKEY(const Channel *channel, const Client &client) {
	// channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :End of /NAMES list");
	//"<client> <channel> :Cannot join channel (+k)"
}

void ERR_CHANNELISFULL(const Channel *channel, const Client &client) {
	// channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :End of /NAMES list");
	//"<client> <channel> :Cannot join channel (+l)"
}

void ERR_INVITEONLYCHAN(const Channel *channel, const Client &client) {
	//channel->sendMessage(client.getUsername() + " " +   channel->getName() + " :End of /NAMES list");
	//"<client> <channel> :Cannot join channel (+i)"
}

void ERR_ALREADYREGISTERED(const Client &client) {
	client.sendMessage(":localhost 462 " + client.getNickname() + " :You may not reregister\r\n");
}

void ERR_NOTREGISTERED(const Client &client) {
	client.sendMessage(":localhost 451 " + client.getNickname() + " :You have not registered\r\n");
}

void ERR_NEEDMOREPARAMS(const Client &client, std::string commandName) {
	client.sendMessage(":localhost 461 " + client.getNickname() + " " + commandName + " :Not enough parameters\r\n");
}

void ERR_NICKNAMEINUSE(const Client &client, std::string nick) {
	client.sendMessage(":localhost 433 " + client.getNickname() + " " + nick + " :Nickname is already in use\r\n");
}

void ERR_NONICKNAMEGIVEN(const Client &client) {
	client.sendMessage(":localhost 431 " + client.getNickname() + " :No nickname given\r\n");
}

void ERR_ERRONEUSNICKNAME(const Client &client, std::string nick) {
	client.sendMessage(":localhost 432 " + client.getNickname() + " " + nick + " :Erroneus nickname\r\n");
}

void ERR_PASSWDMISMATCH(const Client &client) {
	client.sendMessage(":localhost 464 " + client.getNickname() + " :Password incorrect\r\n"); 
}

void RPL_WELCOME(const Client &client) {
	client.sendMessage(":localhost 001 " + client.getNickname() + " :Welcome to the " + NETWORK_NAME + " Network, " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n");
}

void RPL_YOURHOST(const Client &client) {
	client.sendMessage(":localhost 002 " + client.getNickname() + " :Your host is " + SERVER_NAME + ", running on version " + SERVER_VERSION + "\r\n");
}

void RPL_CREATED(const Client &client) {
	// changer
	client.sendMessage(":localhost 003 " + client.getNickname() + " :Your server was created before !\r\n");
}

void RPL_MYINFO(const Client &client) {
	client.sendMessage(":localhost 004 " + client.getNickname() + " " + SERVER_NAME + " " + SERVER_VERSION + " o tpkil k,l\r\n");
}

void RPL_ISUPPORT(const Client &client) {
	client.sendMessage(":localhost 005 " + client.getNickname() + " NICKLEN=" + RULES_NICKLEN + " CHANNELEN=" + RULES_CHANELLEN + " TOPICLEN=" + RULES_TOPICLEN + " :are supported by this server\r\n");
}

void RPL_MOTDSTART(const Client &client) {
	client.sendMessage(":localhost 375 " + client.getNickname() + " :- " + SERVER_NAME + " Message of the day - \r\n");
}

void RPL_MOTD(const Client &client, std::string motd) {
	client.sendMessage(":localhost 372 " + client.getNickname() + " :" + motd + "\r\n");
}

void RPL_ENDOFMOTD(const Client &client) {
	client.sendMessage(":localhost 376 " + client.getNickname() + " :End of /MOTD command.\r\n");
}

void ERR_UNKNOWNCOMMAND(const Client &client) {
	client.sendMessage(":localhost 421 " + client.getNickname() + " : Unknowm command\r\n");
}