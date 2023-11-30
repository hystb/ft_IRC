# include <CommandHandler.hpp>

Channel	*getChannel(Command& cmd, std::string	target) {
	std::map<std::string, Channel*>::iterator channelIt;

	channelIt = cmd.getChannels().find(target);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), target);
		return (NULL);
	}
	return channelIt->second;
}

bool	checkModestring(std::string modeString) {
	if (!modeString[0] || !modeString[1] || modeString[2])
		return (1);// log ?? on liberia ubuntu server -> "MODE :Not enough parameters"
	if (modeString[0] != '-' && modeString[0] != '+')
		return (1);
	if (modeString[1] != 'o' && modeString[1] != 'i' && modeString[1] != 't' && modeString[1] != 'k' && modeString[1] != 'l')
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
	Client *targetClient = cmd.getClient()->getClientFromNickname(cmd.getClients(), modeArgument);

	if (targetClient == NULL) {
		ERR_NOSUCHNICK(*cmd.getClient(), modeArgument);
		return ;
	}
	if (action == '+') {
		channelPtr->setOperator(targetClient);
		RPL_YOUREOPER(*targetClient);
		channelPtr->actualiseMode(*targetClient, action, 'o');
	}
	else {
		channelPtr->unsetOperator(targetClient);
		channelPtr->actualiseMode(*targetClient, action, 'o');
	}
}

void	inviteFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (!modeArgument.empty())
		return ;
	if (action == '+') {
		channelPtr->setInviteOnlyMode();
		channelPtr->actualiseMode(*cmd.getClient(), action, 'i');
	}
	else {
		channelPtr->unsetInviteOnlyMode();	
		channelPtr->actualiseMode(*cmd.getClient(), action, 'i');
	}
}

void	topicFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (!modeArgument.empty())
		return ;
	if (action == '+') {
		channelPtr->setTopicRestriction();
		channelPtr->actualiseMode(*cmd.getClient(), action, 't');
	}
	else {
		channelPtr->unsetTopicRestriction();
		channelPtr->actualiseMode(*cmd.getClient(), action, 't');
	}
}

void	keyFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (action == '+') {
		if (modeArgument.empty())
			return ;
		channelPtr->setPassword(modeArgument);
		channelPtr->actualiseMode(*cmd.getClient(), action, 'k');
	}
	else {
		if (!modeArgument.empty())
			return ;
		channelPtr->setPassword("");
		channelPtr->actualiseMode(*cmd.getClient(), action, 'k');
	}
}

void	limitFlag(Command& cmd, Channel *channelPtr, char action, std::string modeArgument) {
	if (action == '+') {
		if (modeArgument.empty() || isStringNumeric(modeArgument) == false)
			return ;
		channelPtr->setLimit(std::atoi(modeArgument.c_str()));
		channelPtr->actualiseMode(*cmd.getClient(), action, 'l');
	}
	else {
		if (!modeArgument.empty())
			return ;
		channelPtr->setLimit(MAX_CLIENTS);
		channelPtr->actualiseMode(*cmd.getClient(), action, 'l');
	}
}

bool	getArg(Command& cmd, std::string &channelName, char &action, char &flag, std::string &modeArgument) {
	if (cmd.getParameters().size() > 3)
		return false;
	else if (cmd.getParameters().size() < 1 || cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return false;
	}
	channelName = cmd.getParameters().at(0);
	if (cmd.getParameters().size() >= 2 && cmd.getParameters().at(1).size() == 2) {
		action = cmd.getParameters().at(1).at(0);
		flag = cmd.getParameters().at(1).at(1);
	}
	if (cmd.getParameters().size() == 3)
		modeArgument = cmd.getParameters().at(2);
	return true;
}

void CommandHandler::mode(Command& cmd)
{
	Channel 		*channelPtr = NULL;
	std::string		channelName;
	std::string		modeArgument;
	char			action = '\0';
	char			flag = '\0';

	if (!getArg(cmd, channelName, action, flag, modeArgument))
		return ;
 	channelPtr = getChannel(cmd, channelName);
	if (cmd.getParameters().size() == 1) {
		RPL_CHANNELMODEIS(*cmd.getClient(), channelPtr);
		// RPL_CREATIONTIME(*cmd.getClient(), channelPtr);
	}
	if (channelPtr == NULL) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), channelName);
		return ;
	}
	if (!channelPtr->isOperator(cmd.getClient())) {
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), channelPtr);
		return ;
	}
	if (flag && action) {
		if (checkModestring(cmd.getParameters().at(1)))
			return ;
	}
	if (flag == 'o') { operatorFlag(cmd, channelPtr, action, modeArgument); }
	else if (flag == 'i') { inviteFlag(cmd, channelPtr, action, modeArgument); }
	else if (flag == 't') { topicFlag(cmd, channelPtr, action, modeArgument); }
	else if (flag == 'k') { keyFlag(cmd, channelPtr, action, modeArgument); }
	else if (flag == 'l') { limitFlag(cmd, channelPtr, action, modeArgument); }
}

//USER
// o: Give/take channel operator privilege										/mode #nomducanal +o pseudodeutilisateur

//CHANNEL	
// i: Set/remove Invite-only channel											/mode #nomducanal +i
// t: Set/remove the restrictions of operators the TOPIC command to channel		/mode #nomducanal +t
// k: Set/remove the channel key (password)										/mode #nomducanal +k motdepasse
// l: Set/remove the user limit to channel										/mode #nomducanal +l nombre
