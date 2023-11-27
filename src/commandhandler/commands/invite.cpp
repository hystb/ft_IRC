# include <CommandHandler.hpp>

void CommandHandler::invite(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;

	if (cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return ;
	}
	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), cmd.getParameters().at(0));
		return;
	}
	if (it->second->isInviteOnlyMode() && !it->second->isOperator(cmd.getClient())) {
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), it->second);
		return ;
	}
	if (it->second->isMember(cmd.getParameters().at(1))) {
		ERR_USERONCHANNEL(*cmd.getClient(), it->second);
		return ;
	}
	if (!(it->second->isMember(cmd.getClient()))) {
		ERR_NOTONCHANNEL(*cmd.getClient(), it->second);
		return ;
	}
	else {
		// log ici
		RPL_INVITING(*cmd.getClient(), it->second);
		// it->second->addInvited()//pb il me faut le ptr sur le perso quon veut ajouter alors que jai un nickname
	}
}
