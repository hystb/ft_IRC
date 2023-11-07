# include <global.hpp>

// JOIN
void JOIN_MSG(const Client &client, const Channel *channel) {//fait maison apres les deux points
	client.sendMessage(client.getUsername() + " " + channel->getName() + " : joined the server\r\n");
}

void RPL_TOPIC(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
}

void RPL_NAMREPLY(const Client &client, const Channel *channel) {//to do, symbol
	// client.sendMessage(client.getUsername() + " @ " + channel->getName() + " :" + channel->getTopic() + "\r\n");
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}

void RPL_ENDOFNAMES(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :End of /NAMES list\r\n");
}

void ERR_NEEDMOREPARAMS(const Client &client, const Channel *channel, std::string &command) {
	client.sendMessage(client.getUsername() + " " + command +" :Not enough parameters\r\n");
}

void ERR_NOSUCHCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :No such channel\r\n");
}

void ERR_BADCHANNELKEY(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :Cannot join channel (+k)\r\n");
}

void ERR_CHANNELISFULL(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :Cannot join channel (+l)\r\n");
}

void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :Cannot join channel (+i)\r\n");
}
