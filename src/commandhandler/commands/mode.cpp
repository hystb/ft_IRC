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

bool	checkModestring(Command& cmd, Channel *channelPtr, std::string modestring) {
	if (modestring.empty()) {
		RPL_CHANNELMODEIS(*cmd.getClient(), channelPtr);
		// RPL_CREATIONTIME(*cmd.getClient(), channelPtr);
	}
	if (!modestring[0] || !modestring[1] || modestring[2])
		return (1);// log ?? on liberia ubuntu server -> "MODE :Not enough parameters"
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

bool	getArg(Command& cmd, std::string &channelName, char &action, char &flag, std::string &modeArgument) {
	if (cmd.getParameters().size() > 3)
		return (1);
	if (cmd.getParameters().size() >= 1)
		channelName = cmd.getParameters().at(0);
	if (cmd.getParameters().size() >= 2 && cmd.getParameters().at(1).size() == 2) {
		action = cmd.getParameters().at(1).at(0);
		flag = cmd.getParameters().at(1).at(1);
	}
	if (cmd.getParameters().size() == 3)
		modeArgument = cmd.getParameters().at(2);
	return (0);
}

void CommandHandler::mode(Command& cmd)
{
	std::string		channelName;
	char			action;
	char			flag;
	std::string		modeArgument;
	Channel 		*channelPtr;

	if (getArg(cmd, channelName, action, flag, modeArgument))
		return ;
	// if (channelName.empty()) { // a verifier si on dois le mettre dans mode
	// 	ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
	// 	return ;
	// }
 	channelPtr = getChannel(cmd, channelName);
	if (channelPtr == NULL) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(), channelName);
		return ;
	}
	if (!channelPtr->isOperator(cmd.getClient())) {
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), channelPtr);
		return ;
	}
	if (cmd.getParameters().size() >= 2 && cmd.getParameters().at(1).size() == 2)
		if (checkModestring(cmd, channelPtr, cmd.getParameters().at(1)))
			return ;
	if (flag == 'o') {
		operatorFlag(cmd, channelPtr, action, modeArgument);
	}
	else {
		if (flag == 'i') { inviteFlag(cmd, channelPtr, action, modeArgument); }
		else if (flag == 't') { topicFlag(cmd, channelPtr, action, modeArgument); }
		else if (flag == 'k') { keyFlag(cmd, channelPtr, action, modeArgument); }
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
