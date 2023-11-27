# include <global.hpp>

bool	getArg(Command& cmd, Client*& invitedClient, std::string& clientName, std::string& channelName) {
	if (cmd.getParameters().size() > 2)
		return (1);
	else if (cmd.getParameters().size() != 2 || cmd.getParameters().at(0).empty() || cmd.getParameters().at(1).empty()) {
		ERR_NEEDMOREPARAMS(*cmd.getClient(), cmd.getCommand());
		return (1);
	}
	clientName = cmd.getParameters().at(0);
	channelName = cmd.getParameters().at(1);
	invitedClient = cmd.getClient()->getClientFromNickname(cmd.getClients(), clientName);
	if (invitedClient == NULL)
		return (1);//no such client on server, log ?
	return (0);
}

void CommandHandler::invite(Command& cmd)
{
	std::map<std::string, Channel*>::iterator	channelIt;
	Client										*invitedClient = NULL;
	std::string									clientName;
	std::string									channelName;

	if (getArg(cmd, invitedClient, clientName, channelName))
		return ;
	channelIt = cmd.getChannels().find(channelName);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*cmd.getClient(),channelName);
		return ;
	}
	if (!cmd.getClient()->getClientFromNickname(cmd.getClients(), clientName))
		return ;
	if (channelIt->second->isInviteOnlyMode() && !channelIt->second->isOperator(cmd.getClient())) {
		ERR_CHANOPRIVSNEEDED(*cmd.getClient(), channelIt->second);
		return ;
	}
	if (channelIt->second->isMember(clientName)) {
		ERR_USERONCHANNEL(*cmd.getClient(), channelIt->second);
		return ;
	}
	if (!(channelIt->second->isMember(cmd.getClient()))) {
		ERR_NOTONCHANNEL(*cmd.getClient(), channelIt->second);
		return ;
	}
	else {
		RPL_INVITING(*cmd.getClient(), *invitedClient, channelIt->second);
		channelIt->second->addInvited(invitedClient);
	}
}
