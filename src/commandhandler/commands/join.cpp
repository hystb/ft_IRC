# include <global.hpp>
	
bool	getArg(Command& cmd, std::string &channelName, std::string &password) {
	if (cmd.getParameters().size() > 2)
		return (1);
	if (cmd.getParameters().size() >= 1)
		channelName = cmd.getParameters().at(0);
	else
		return (1);
	if (cmd.getParameters().size() >= 2)
		password = cmd.getParameters().at(1);
	if (channelName.empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return (1);
	}
	if (channelName.at(0) != '#' || channelName.find('#', 2) != std::string::npos) {
		return (1);
	}
	return (0);
}

void CommandHandler::join(Command& cmd)
{
	std::map<std::string, Channel*>::iterator	channelIt;
	std::string									channelName;
	std::string									password;
	
	if (getArg(cmd, channelName, password))
		return ;
	channelIt = cmd.getChannels().find(channelName);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), channelName);
		cmd.getChannels()[channelName] = new Channel(channelName, cmd.getClient());
		if (!password.empty())
			cmd.getChannels().at(channelName)->setPassword(password);
		LOG_JOIN(*cmd.getClient(), cmd.getChannels()[channelName]);
		RPL_TOPIC(*cmd.getClient(), cmd.getChannels()[channelName]);
		cmd.getChannels()[channelName]->actualiseClientsList();
		return ;
	}
	else if (channelIt->second->isMember(cmd.getClient()->getNickname())) {
		return ;
	}
	else if (channelIt->second->isInviteOnlyMode() && !(channelIt->second->isInvited(cmd.getClient()->getNickname()))) {
		ERR_INVITEONLYCHAN(*cmd.getClient(), channelIt->second);
		return ;
	}
	else if (cmd.getChannels().size() >= channelIt->second->getLimit()) {
		ERR_CHANNELISFULL(*cmd.getClient(), channelIt->second);
		return ;
	}
	else if (!channelIt->second->getPassword().empty() && password != channelIt->second->getPassword()) {
		ERR_BADCHANNELKEY(*cmd.getClient(), channelIt->second);
		return ;
	}
	else {
		channelIt->second->addClient(cmd.getClient(), 0);
		LOG_JOIN(*cmd.getClient(), channelIt->second);
		RPL_TOPIC(*cmd.getClient(), channelIt->second);
		cmd.getChannels()[channelName]->actualiseClientsList();
	}
}
