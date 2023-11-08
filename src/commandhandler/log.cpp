# include <global.hpp>

void RPL_TOPIC(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
}

void RPL_NAMREPLY(const Client &client, const Channel *channel) {//to do
	client.sendMessage(client.getUsername() + " @ " + channel->getName() + " :" + channel->getTopic() + "\r\n");
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}

void ERR_NEEDMOREPARAMS(const Client &client, const Channel *channel, const std::string &command) {
	client.sendMessage(client.getUsername() + " " + command +" :Not enough parameters\r\n");
}

void JOIN_MSG(const Client &client, const Channel *channel) {//fait maison apres les deux points
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :Joined the server\r\n");
}

void RPL_ENDOFNAMES(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :End of /NAMES list\r\n");
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

void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :You're not channel operator\r\n");
}

void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :They aren't on that channel\r\n");
}

void ERR_NOTONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + channel->getName() + " :You're not on that channel\r\n");
}

void ERR_USERONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + client.getNickname() + " " + channel->getName() + " :is already on channel\r\n");
}

void RPL_INVITING(const Client &client, const Channel *channel) {
	client.sendMessage(client.getUsername() + " " + client.getNickname() + " " + channel->getName() + "\r\n");
}
