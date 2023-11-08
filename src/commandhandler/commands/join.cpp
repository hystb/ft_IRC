# include <global.hpp>

void CommandHandler::join(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;

	if (cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), it->second, cmd.getCommand());
	}
	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), it->second);
		cmd.getChannels().insert(std::pair<std::string, Channel*>(cmd.getParameters().at(0), \
		new Channel(cmd.getParameters().at(0), cmd.getParameters().at(1), cmd.getClient())));
		return ;
	}
	else if (!(it->second->isInvited(cmd.getClient()->getUsername()))) {
		ERR_INVITEONLYCHAN(*cmd.getClient(), it->second);
		return ;
	}
	else if (it->second->getLimit() >= cmd.getChannels().size()) {
		ERR_CHANNELISFULL(*cmd.getClient(), it->second);
	}
	else if (cmd.getParameters().at(1) != it->second->getPassword()) {
		ERR_BADCHANNELKEY(*cmd.getClient(), it->second);
		return ;
	}
	else {
		JOIN_MSG(*cmd.getClient(), it->second);
		RPL_TOPIC(*cmd.getClient(), it->second);
		RPL_NAMREPLY(*cmd.getClient(), it->second);
		RPL_ENDOFNAMES(*cmd.getClient(), it->second);
		it->second->addClient(cmd.getClient(), 0);
	}
}
