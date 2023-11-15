# include <global.hpp>

void ERR_BADCHANNELKEY(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 475 " + client.getUsername() + " " + channel->getName() + " :Cannot join channel (+k)\r\n");
}

void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 482 " + client.getUsername() + " " + channel->getName() + " :You're not channel operator\r\n");
}

void ERR_CHANNELISFULL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 471 " + client.getUsername() + " " + channel->getName() + " :Cannot join channel (+l)\r\n");
}

void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 473 " + client.getUsername() + " " + channel->getName() + " :Cannot join channel (+i)\r\n");
}

void ERR_NEEDMOREPARAMS(const Client &client, const Channel *channel, const std::string &command) {
	client.sendMessage(":localhost 461 " + client.getUsername() + " " + command +" :Not enough parameters\r\n");
}

// void ERR_NOSUCHCHANNEL(const Client &client, const std::string channelName) {
// 	client.sendMessage(client.getUsername() + " " + channelName + " :No such channel\r\n");
// }

void ERR_NOTONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 442 " + client.getUsername() + " " + channel->getName() + " :You're not on that channel\r\n");
}

void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 441 " + client.getUsername() + " " + channel->getName() + " :They aren't on that channel\r\n");
}

void ERR_USERONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 443 " + client.getUsername() + " " + client.getNickname() + " " + channel->getName() + " :is already on channel\r\n");
}

void LOG_JOIN(const Client &client, const Channel *channel) {//fait maison apres les deux points
	client.sendMessage(Client::getClientID(client) + " JOIN " + channel->getName() + "\r\n"); // c'est ça que j'ai fix
}

void LOG_KICK(const Client &client, const Channel *channel) {//fait maison apres les deux points
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :Kicked out of the server\r\n");
}

void RPL_ENDOFNAMES(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 366 " + client.getUsername() + " " + channel->getName() + " :End of /NAMES list\r\n");
}

void RPL_INVITING(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 341 " + client.getUsername() + " " + client.getNickname() + " " + channel->getName() + "\r\n");
}

void RPL_NAMREPLY(const Client &client, const Channel *channel) {//to do
	client.sendMessage(":localhost 353 " + client.getUsername() + " @ " + channel->getName() + " :" + channel->getTopic() + "\r\n");
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}

void RPL_TOPIC(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 332 " + client.getUsername() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
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
	client.sendMessage(":localhost 003 " + client.getNickname() + " :Your server was created 15th october 1996 !\r\n");
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

void ERR_NOSUCHCHANNEL(const Client &client, std::string channel) {
	client.sendMessage(":localhost 403 " + client.getNickname() + " " + channel + " :No such channel\r\n");
}

void ERR_NOSUCHNICK(const Client &client, std::string nick) {
	client.sendMessage(":localhost 401 " + client.getNickname() + " " + nick + " :No such nick\r\n");
}

void ERR_NOTEXTTOSEND(const Client &client) {
	client.sendMessage(":localhost 412 " + client.getNickname() + " :No text to send\r\n");
}

void ERR_CANNOTSENDTOCHAN(const Client &client, std::string target) {
	client.sendMessage(":localhost 404 " + client.getNickname() + " " + target + " :Cannot send to channel\r\n");
}
