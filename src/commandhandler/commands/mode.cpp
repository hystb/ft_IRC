# include <global.hpp>

Channel	*getChannel(Command& cmd, std::string	target) {
	std::map<std::string, Channel*>::iterator channelIt;

	channelIt = cmd.getChannels().find(target);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), target);
		return (NULL);
	}
	return channelIt->second;
}

bool	checkModestring(std::string modestring) {
	if (modestring.empty() || !modestring[0] || !modestring[1] || modestring[2])
		return (1);
	if (modestring[0] != '-' && modestring[0] != '+')
		return (1);
	if (modestring[1] != 'o' && modestring[1] != 'i' && modestring[1] != 't' && modestring[1] != 'k' && modestring[1] != 'l')
		return (1);
}

//USER
// o: Give/take channel operator privilege										/mode #nomducanal +o pseudodeutilisateur

//CHANNEL	
// i: Set/remove Invite-only channel											/mode #nomducanal +i
// t: Set/remove the restrictions of operators the TOPIC command to channel		/mode #nomducanal +t
// k: Set/remove the channel key (password)										/mode #nomducanal +k motdepasse
// l: Set/remove the user limit to channel										/mode #nomducanal +l nombre

void	operatorFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (modeArgument.empty())
		return ;
	Client *client = cmd.getClient()->getClientFromNickname(cmd.getClients(), modeArgument);
	if (client == NULL)//le client existe pas
		return ;
	if (action == '+')
		channelPtr->setOperator(client);//log?
	else
		channelPtr->unsetOperator(client);
}

void	inviteFlag(Channel *channelPtr, char action, std::string modeArgument) {
	if (!modeArgument.empty())
		return ;
	if (action == '+')
		channelPtr->setInviteOnlyMode();
	else
		channelPtr->unsetInviteOnlyMode();	
}

void	topicFlag(Channel *channelPtr, char action, std::string modeArgument) {
	if (!modeArgument.empty())
		return ;
	if (action == '+')
		channelPtr->setTopicRestriction();
	else
		channelPtr->unsetTopicRestriction();
}

void	keyFlag(Channel *channelPtr, char action, std::string modeArgument) {
	if (modeArgument.empty())
		return ;
}

void	limitFlag(Channel *channelPtr, char action, std::string modeArgument) {
	if (modeArgument.empty())
		return ;
}

void CommandHandler::mode(Command& cmd)
{
	const std::string	&channelName = cmd.getParameters().at(0);
	const std::string	&modeArgument = cmd.getParameters().at(2);
	char				action = cmd.getParameters().at(1).at(0);
	char				flag = cmd.getParameters().at(1).at(1);
	Channel 			*channelPtr;
	

	if (channelName.empty()) { // a verifier si on dois le mettre dans mode
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return ;
	}
 	channelPtr = getChannel(cmd, cmd.getParameters().at(0));
	if (channelPtr == NULL)
		return ;
	if (checkModestring(cmd.getParameters().at(1))) {
		return ;
	}
	if (flag == 'o') {
		operatorFlag(cmd, channelPtr, action, modeArgument);
	}
	else {
		if (flag == 'i') { inviteFlag(channelPtr, action, modeArgument); }
		else if (flag == 't') { topicFlag(channelPtr, action, modeArgument); }
		else if (flag == 'k') { keyFlag(channelPtr, action, modeArgument); }
		else if (flag == 'l') { limitFlag(channelPtr, action, modeArgument); }
	}
}
