# include <global.hpp>

void CommandHandler::kick(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;

	if (cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), it->second, cmd.getCommand());
		return ;
	}
	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), it->second);
		return;
	}
	else if (!it->second->isOperator(cmd.getClient())) {
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), it->second);
		return ;
	}
	else if (!it->second->isMember(cmd.getParameters().at(1))) {
		ERR_USERNOTINCHANNEL(*cmd.getClient(), it->second);
		return ;
	}
	else if (!(it->second->isMember(cmd.getClient()))) {
		ERR_NOTONCHANNEL(*cmd.getClient(), it->second);
		return ;
	}
	else {
		it->second->removeClient(cmd.getClient());
		//kick log
	}
}