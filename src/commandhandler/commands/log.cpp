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
	client.sendMessage(client.getNickname() + " :You may not reregister\r\n");
}

void ERR_NOTREGISTERED(const Client &client) {
	client.sendMessage(client.getNickname() + " :You have not registered\r\n");
}