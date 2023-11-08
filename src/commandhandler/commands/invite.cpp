# include <global.hpp>

void CommandHandler::invite(Command& cmd)
{
	std::map<std::string, Channel*>::iterator it;

	if (cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), it->second, cmd.getCommand());
	}
	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), it->second);
		return;
	}
	if (0) { //channel is on mode invite only and user is not operator)
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), it->second);
		return ;
	}
	if ((it->second->isMember(cmd.getClient()))) { // celui qui est invité est deja sur le channel
		// probleme ils sont listé par username et non par nickname dans la map -> change la map?
		ERR_USERONCHANNEL(*cmd.getClient(), it->second);
	}
	if (!(it->second->isMember(cmd.getClient()))) { //celui qui veut inviter n'est pas sur le channel
		ERR_NOTONCHANNEL(*cmd.getClient(), it->second);
		return ;
	}
	else {
		it->second->addClient(cmd.getClient(), 0);
		RPL_INVITING(*cmd.getClient(), it->second);
	}
}
