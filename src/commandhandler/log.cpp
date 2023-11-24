# include <global.hpp>

void RPL_WELCOME(const Client &client) {
	client.sendMessage(":localhost 001 " + client.getNickname() + " :Welcome to the " + NETWORK_NAME + " Network, " + client.getNickname() + "!" + client.getUsername() + "@localhost");
}

void RPL_YOURHOST(const Client &client) {
	client.sendMessage(":localhost 002 " + client.getNickname() + " :Your host is " + SERVER_NAME + ", running on version " + SERVER_VERSION);
}

void RPL_CREATED(const Client &client) {
	client.sendMessage(":localhost 003 " + client.getNickname() + " :Your server was created 15th october 1996 !");
}

void RPL_MYINFO(const Client &client) {
	client.sendMessage(":localhost 004 " + client.getNickname() + " " + SERVER_NAME + " " + SERVER_VERSION + " o tpkil k,l");
}

void RPL_ISUPPORT(const Client &client) {
	client.sendMessage(":localhost 005 " + client.getNickname() + " NICKLEN=" + RULES_NICKLEN + " CHANNELEN=" + RULES_CHANELLEN + " TOPICLEN=" + RULES_TOPICLEN + " :are supported by this server");
}

// void RPL_UMODEIS(const Client &client) {
// 	client.sendMessage(":localhost 221 " + client.getNickname() + " +c");
// }

void RPL_CHANNELMODEIS(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 324 " + client.getNickname() + " " + channel->getName() + " " + channel->getModes());
 	//"<client> <channel> <modestring> <mode arguments>..."
}

// void RPL_CREATIONTIME(const Client &client, const Channel *channel) {
// 	client.sendMessage(":localhost 329 " + client.getNickname() + " " + channel->getName() + " 1633648400");
//   	//"<client> <channel> <creationtime>"
// 	//1633648400" est le timestamp représentant la date de création du canal. Ce timestamp est généralement au format UNIX, qui compte les secondes écoulées depuis le 1er janvier 1970 à 00:00:00 UTC.
// }

void RPL_TOPIC(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 332 " + client.getNickname() + " " + channel->getName() + " :" + channel->getTopic());
}

void RPL_INVITING(const Client &client, const Client &invited, const Channel *channel) {
	client.sendMessage(":localhost 341 " + client.getNickname() + " " + invited.getNickname() + " " + channel->getName());
}

void RPL_NAMREPLY(const Client &client, Channel *channel) {
	client.sendMessage(":localhost 353 " + client.getNickname()  + " = " + channel->getName() + " :" + channel->listClients());
}

void RPL_ENDOFNAMES(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 366 " + channel->getName() + " :End of /NAMES list");
}

void RPL_MOTD(const Client &client, std::string motd) {
	client.sendMessage(":localhost 372 " + client.getNickname() + " :" + motd);
}

void RPL_MOTDSTART(const Client &client) {
	client.sendMessage(":localhost 375 " + client.getNickname() + " :- " + SERVER_NAME + " Message of the day - ");
}

void RPL_ENDOFMOTD(const Client &client) {
	client.sendMessage(":localhost 376 " + client.getNickname() + " :End of /MOTD command.");
}

void ERR_NOSUCHNICK(const Client &client, std::string nick) {
	client.sendMessage(":localhost 401 " + client.getNickname() + " " + nick + " :No such nick");
}

void ERR_NOSUCHCHANNEL(const Client &client, std::string channel) {
	client.sendMessage(":localhost 403 " + client.getNickname() + " " + channel + " :No such channel");
}

void ERR_CANNOTSENDTOCHAN(const Client &client, std::string target) {
	client.sendMessage(":localhost 404 " + client.getNickname() + " " + target + " :Cannot send to channel");
}

void ERR_NOTEXTTOSEND(const Client &client) {
	client.sendMessage(":localhost 412 " + client.getNickname() + " :No text to send");
}

void ERR_UNKNOWNCOMMAND(const Client &client) {
	client.sendMessage(":localhost 421 " + client.getNickname() + " : Unknowm command");
}

void ERR_NONICKNAMEGIVEN(const Client &client) {
	client.sendMessage(":localhost 431 " + client.getNickname() + " :No nickname given");
}

void ERR_ERRONEUSNICKNAME(const Client &client, std::string nick) {
	client.sendMessage(":localhost 432 " + client.getNickname() + " " + nick + " :Erroneus nickname");
}

void ERR_NICKNAMEINUSE(const Client &client, std::string nick) {
	client.sendMessage(":localhost 433 " + client.getNickname() + " " + nick + " :Nickname is already in use");
}

void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 441 " + client.getNickname() + " " + channel->getName() + " :They aren't on that channel");
}

void ERR_NOTONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 442 " + client.getNickname() + " " + channel->getName() + " :You're not on that channel");
}

void ERR_USERONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 443 " + client.getNickname() + " " + client.getNickname() + " " + channel->getName() + " :is already on channel");
}

void ERR_NOTREGISTERED(const Client &client) {
	client.sendMessage(":localhost 451 " + client.getNickname() + " :You have not registered");
}

void ERR_NEEDMOREPARAMS(const Client &client, std::string commandName) {
	client.sendMessage(":localhost 461 " + client.getNickname() + " " + commandName + " :Not enough parameters");
}

void ERR_ALREADYREGISTERED(const Client &client) {
	client.sendMessage(":localhost 462 " + client.getNickname() + " :You may not reregister");
}

void ERR_PASSWDMISMATCH(const Client &client) {
	client.sendMessage(":localhost 464 " + client.getNickname() + " :Password incorrect"); 
}

void ERR_CHANNELISFULL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 471 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+l)");
}

void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 473 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+i)");
}

void ERR_BADCHANNELKEY(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 475 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+k)");
}

void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 482 " + client.getNickname() + " " + channel->getName() + " :You're not channel operator");
}

void ERR_UMODEUNKNOWNFLAG(const Client &client) {
	client.sendMessage(":localhost 501 " + client.getNickname() + "  :Unknown MODE flag");
}

void LOG_JOIN(const Client &client, const Channel *channel) {
	client.sendMessage(Client::getClientID(client) + " JOIN " + channel->getName());
}

