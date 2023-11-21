# include <global.hpp>

void CommandHandler::join(Command& cmd)
{
	std::map<std::string, Channel*>::iterator channelIt;
	const std::string	&channelName = cmd.getParameters().at(0);

	if (channelName.empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return ;
	}
	channelIt = cmd.getChannels().find(channelName);
	if (channelName.at(0) != '#') {
		std::cout << "et le # c'est pour les chiens ?" << std::endl;
		return ;
	}
	else if (channelName.find('#', 2) != std::string::npos) {
		std::cout << "un # de trop..." << std::endl;
		return ;
	}
	else if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), channelName);
		cmd.getChannels()[channelName] = new Channel(channelName, cmd.getClient());
		if (cmd.getParameters().size() > 1)
			cmd.getChannels().at(channelName)->setPassword(cmd.getParameters().at(1));
		LOG_JOIN(*cmd.getClient(), cmd.getChannels()[channelName]);
		RPL_TOPIC(*cmd.getClient(), cmd.getChannels()[channelName]);
		cmd.getChannels()[channelName]->actualiseClientsList();
		return ;
	}
	else if (channelIt->second->isMember(cmd.getClient()->getNickname())) {
		std::cout << "tes deja membre frerot" << std::endl;
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
	else if (!channelIt->second->getPassword().empty() && cmd.getParameters().at(1) != channelIt->second->getPassword()) {
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
