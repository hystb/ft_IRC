# include <global.hpp>

void CommandHandler::join(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;
	const std::string	&chanelName = cmd.getParameters().at(0);

	if (chanelName.empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), it->second, cmd.getCommand());
		return ;
	}
	it = cmd.getChannels().find(chanelName);
	if (chanelName.at(0) != '#') {
		std::cout << "et le # c'est pour les chiens ?" << std::endl;
		return ;
	}
	else if (chanelName.find('#', 2) != std::string::npos) {
		std::cout << "un # de trop..." << std::endl;
		return ;
	}
	else if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), chanelName);
		cmd.getChannels()[chanelName] = new Channel(chanelName, cmd.getClient());
		if (cmd.getParameters().size() > 1)
			cmd.getChannels().at(chanelName)->setPassword(cmd.getParameters().at(1));
		LOG_JOIN(*cmd.getClient(), cmd.getChannels()[chanelName]);
		RPL_TOPIC(*cmd.getClient(), cmd.getChannels()[chanelName]);
		RPL_NAMREPLY(*cmd.getClient(), cmd.getChannels()[chanelName]);
		RPL_ENDOFNAMES(*cmd.getClient(), cmd.getChannels()[chanelName]);
		// cmd.listChannel();//test
		cmd.getChannels()[chanelName]->listClients();//test
		return ;
	}
	else if (it->second->isMember(cmd.getClient()->getNickname())) {
		std::cout << "tes deja membre frerot" << std::endl;
		return ;
	}
	else if (it->second->isInviteOnlyMode() && !(it->second->isInvited(cmd.getClient()->getNickname()))) {
		ERR_INVITEONLYCHAN(*cmd.getClient(), it->second);
		return ;
	}
	else if (cmd.getChannels().size() >= it->second->getLimit()) {
		ERR_CHANNELISFULL(*cmd.getClient(), it->second);
		return ;
	}
	else if (!it->second->getPassword().empty() && cmd.getParameters().at(1) != it->second->getPassword()) {
		ERR_BADCHANNELKEY(*cmd.getClient(), it->second);
		return ;
	}
	else {
		it->second->addClient(cmd.getClient(), 0);
		LOG_JOIN(*cmd.getClient(), it->second);
		RPL_TOPIC(*cmd.getClient(), it->second);
		RPL_NAMREPLY(*cmd.getClient(), it->second);
		RPL_ENDOFNAMES(*cmd.getClient(), it->second);
		// cmd.listChannel();
	}
}
