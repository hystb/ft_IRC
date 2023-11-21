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

//checl modearg parsing
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







// 	const std::string	&channelName = cmd.getParameters().at(0);

// 	if (channelName.empty()) {
// 		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
// 		return ;
// 	}
// 	if (channelName.at(0) != '#') {
// 		std::cout << "et le # c'est pour les chiens ?" << std::endl;
// 		return ;
// 	}
// 	else if (channelName.find('#', 2) != std::string::npos) {
// 		std::cout << "un # de trop..." << std::endl;
// 		return ;
// 	}
// 		cmd.getChannels()[channelName] = new Channel(channelName, cmd.getClient());
// 		if (cmd.getParameters().size() > 1)
// 			cmd.getChannels().at(channelName)->setPassword(cmd.getParameters().at(1));
// 		LOG_JOIN(*cmd.getClient(), cmd.getChannels()[channelName]);
// 		RPL_TOPIC(*cmd.getClient(), cmd.getChannels()[channelName]);
// 		cmd.getChannels()[channelName]->actualiseClientsList();
// 		return ;
// 	}
// 	else if (channelIt->second->isMember(cmd.getClient()->getNickname())) {
// 		std::cout << "tes deja membre frerot" << std::endl;
// 		return ;
// 	}
// 	else if (channelIt->second->isInviteOnlyMode() && !(channelIt->second->isInvited(cmd.getClient()->getNickname()))) {
// 		ERR_INVITEONLYCHAN(*cmd.getClient(), channelIt->second);
// 		return ;
// 	}
// 	else if (cmd.getChannels().size() >= channelIt->second->getLimit()) {
// 		ERR_CHANNELISFULL(*cmd.getClient(), channelIt->second);
// 		return ;
// 	}
// 	else if (!channelIt->second->getPassword().empty() && cmd.getParameters().at(1) != channelIt->second->getPassword()) {
// 		ERR_BADCHANNELKEY(*cmd.getClient(), channelIt->second);
// 		return ;
// 	}






// 	std::vector<std::string> 	param = cmd.getParameters();
// 	Client					 	*client = cmd.getClient();
// 	std::string					channelName;

// 	// MODE - Change the channel’s mode:
// 	// · i: Set/remove Invite-only channel
// 	// · t: Set/remove the restrictions of the TOPIC command to channel
// 	// · k: Set/remove the channel key (password)
// 	// · o: Give/take channel operator privilege
// 	// · l: Set/remove the user limit to channel

// 	// std::vector<std::string> 	param = cmd.getParameters();
// 	// Client					 	*client = cmd.getClient();
// 	// std::string					channelName;


// 	if (param.size() == 0)
// 		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
// 	channelName = param.at(0);
// 	if (cmd.getChannels().find(channelName) == cmd.getChannels().end())
// 		return (ERR_NOSUCHCHANNEL(*client, channelName));
// 	if (param.size() > 1)
// 	{

// 	}
// 	else
// 		return ;
// }