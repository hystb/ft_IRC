# include <global.hpp>

bool	getArg(Command& cmd, Client*& client, std::string &channelName, std::string &password) {
	if (cmd.getParameters().size() > 2)
		return false;
	else if (cmd.getParameters().size() < 1 || cmd.getParameters().at(0).empty()) {
		ERR_NEEDMOREPARAMS(*client, cmd.getCommand());
		return false;
	}
	channelName = cmd.getParameters().at(0);
	if (cmd.getParameters().size() == 2 && !cmd.getParameters().at(1).empty())
		password = cmd.getParameters().at(1);
	if (channelName.at(0) != '#' || channelName.find('#', 2) != std::string::npos) {
		return false;
	}
	return true;
}

void CommandHandler::join(Command& cmd)
{
	std::string									channelName;
	std::string									password;
	Client*										client = cmd.getClient();
	Channel*									channel = NULL;
	
	if (!getArg(cmd, client, channelName, password))
		return ;

	std::map<std::string, Channel*>::iterator channelIt = cmd.getChannels().find(channelName);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*client, channelName);
		cmd.getChannels()[channelName] = new Channel(channelName, client);
		channel = cmd.getChannels()[channelName];
		std::cout << password << std::endl;
		if (!password.empty()) {
			cmd.getChannels().at(channelName)->setPassword(password);
			channel->actualiseMode(*cmd.getClient(), '+', 'k');
		}
		LOG_JOIN(*client, channel);
		RPL_TOPIC(*client, channel);
		channel->actualiseClientsList();
		return ;
	}
	channel = channelIt->second;
	if (channel->isMember(client->getNickname())) {
		return ;
	}
	else if (channel->isInviteOnlyMode() && !(channel->isInvited(client->getNickname()))) {
		ERR_INVITEONLYCHAN(*client, channel);
		return ;
	}
	else if (channel->getClients().size()  >= channel->getLimit()) {
		ERR_CHANNELISFULL(*client, channel);
		return ;
	}
	else if (!channel->getPassword().empty() && password != channel->getPassword()) {
		ERR_BADCHANNELKEY(*client, channel);
		return ;
	}

	channel->addClient(client, 0);
	LOG_JOIN(*client, channel);
	RPL_TOPIC(*client, channel);
	channel->actualiseClientsList();
}
