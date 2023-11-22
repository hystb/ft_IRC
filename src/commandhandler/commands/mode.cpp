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
	return (0);
}

bool isStringNumeric(std::string& str) {
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }
    return true;
}

void	operatorFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (modeArgument.empty())
		return ;
	Client *client = cmd.getClient()->getClientFromNickname(cmd.getClients(), modeArgument);
	if (client == NULL) {
		ERR_NOSUCHNICK(*cmd.getClient(), modeArgument);
		return ;
	}
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
	if (action == '+') {
		if (modeArgument.empty())
			return ;
		channelPtr->setPassword(modeArgument);
	}
	else {
		if (!modeArgument.empty())
			return ;
		channelPtr->setPassword(NULL);
	}
}

void	limitFlag(Channel *channelPtr, char action, std::string modeArgument) {
	if (action == '+') {
		if (modeArgument.empty() || isStringNumeric(modeArgument) == false)
			return ;
		channelPtr->setLimit(std::atoi(modeArgument.c_str()));
	}
	else {
		if (!modeArgument.empty())
			return ;
		channelPtr->setLimit(MAX_CLIENTS);
	}
}

void CommandHandler::mode(Command& cmd)
{
	const std::string	&channelName = cmd.getParameters().at(0);
	const std::string	&modeArgument = cmd.getParameters().at(2);
	char				action = cmd.getParameters().at(1).at(0);
	char				flag = cmd.getParameters().at(1).at(1);
	Channel 			*channelPtr;
	
	if (!cmd.getParameters().at(3).empty())// si trop darg
		return ;
	if (channelName.empty()) { // a verifier si on dois le mettre dans mode
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return ;
	}
 	channelPtr = getChannel(cmd, cmd.getParameters().at(0));//channel existe pas
	if (channelPtr == NULL)
		return ;
	if (!channelPtr->isOperator(cmd.getClient())) //si il est pas operator, LOG A RAJOUTER
		return ;
	if (checkModestring(cmd.getParameters().at(1))) //pas bon format pour modestring
		return ;
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

//USER
// o: Give/take channel operator privilege										/mode #nomducanal +o pseudodeutilisateur

//CHANNEL	
// i: Set/remove Invite-only channel											/mode #nomducanal +i
// t: Set/remove the restrictions of operators the TOPIC command to channel		/mode #nomducanal +t
// k: Set/remove the channel key (password)										/mode #nomducanal +k motdepasse
// l: Set/remove the user limit to channel										/mode #nomducanal +l nombre
