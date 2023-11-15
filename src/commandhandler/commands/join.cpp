# include <global.hpp>

void CommandHandler::join(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;

	if (cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), it->second, cmd.getCommand());
	}
	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), cmd.getParameters().at(0));
		cmd.getChannels()[cmd.getParameters().at(0)] = new Channel(cmd.getParameters().at(0), cmd.getClient());
		if (cmd.getParameters().size() > 1)
			cmd.getChannels().at(cmd.getParameters().at(0))->setPassword(cmd.getParameters().at(1));
		LOG_JOIN(*cmd.getClient(), cmd.getChannels()[cmd.getParameters().at(0)]);
		RPL_TOPIC(*cmd.getClient(), cmd.getChannels()[cmd.getParameters().at(0)]);
		RPL_NAMREPLY(*cmd.getClient(), cmd.getChannels()[cmd.getParameters().at(0)]);
		RPL_ENDOFNAMES(*cmd.getClient(), cmd.getChannels()[cmd.getParameters().at(0)]);
		// cmd.listChannel();
		cmd.getChannels()[cmd.getParameters().at(0)]->listClients();
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
