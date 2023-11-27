# include <global.hpp>

bool	getArguments3(Command& cmd, Client*& invitedClient, std::string& clientNick, std::string& channelName) {
	if (cmd.getParameters().size() > 2)
		return false;
	else if (cmd.getParameters().size() != 2 || cmd.getParameters().at(0).empty() || cmd.getParameters().at(1).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return false;
	}
	clientNick = cmd.getParameters().at(0);
	channelName = cmd.getParameters().at(1);
	invitedClient = cmd.getClient()->getClientFromNickname(cmd.getClients(), clientNick);
	if (invitedClient == NULL)
		return false;//no such client on server, log ?
	return true;
}

void CommandHandler::invite(Command& cmd)
{
	Client*			invitingClient = cmd.getClient();
	Client*			invitedClient = NULL;
	Channel*		channel = NULL;
	std::string		clientNick;
	std::string		channelName;

	if (!getArguments3(cmd, invitedClient, clientNick, channelName))
		return ;

	std::map<std::string, Channel*>::iterator channelIt = cmd.getChannels().find(channelName);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(),channelName);
		return ;
	}
	channel = channelIt->second;
	if (!invitingClient->getClientFromNickname(cmd.getClients(), clientNick))
		return ;
	if (channel->isInviteOnlyMode() && !channel->isOperator(invitingClient)) {
		ERR_CHANOPRIVSNEEDED(*invitingClient, channel);
		return ;
	}
	if (channel->isMember(clientNick)) {
		ERR_USERONCHANNEL(*invitingClient, channel);
		return ;
	}
	if (!(channel->isMember(invitingClient))) {
		ERR_NOTONCHANNEL(*invitingClient, channel);
		return ;
	}
	
	RPL_INVITING(*invitingClient, *invitedClient, channel);
	channel->addInvited(invitedClient);
}
