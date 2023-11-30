/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:54:37 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

bool	getArguments1(Command& cmd, Client*& client, std::string &channelName, std::string &clientNick) {

	if (cmd.getParameters().size() < 2 || cmd.getParameters().at(0).empty() || cmd.getParameters().at(1).empty()) {
		ERR_NEEDMOREPARAMS(*client, cmd.getCommand());
		return false;
	}
	channelName = cmd.getParameters().at(0);
	clientNick = cmd.getParameters().at(1);
	return true;
}


void CommandHandler::kick(Command& cmd)
{
	std::string		channelName;
	std::string		clientNick;
	Client*			client = cmd.getClient();
	Channel*		channel = NULL;

	if (!getArguments1(cmd, client, channelName, clientNick))
		return ;

	std::map<std::string, Channel*>::iterator channelIt = cmd.getChannels().find(channelName);
	if (channelIt == cmd.getChannels().end()) {
		ERR_NOSUCHCHANNEL(*client, channelName);
		return;
	}
	channel = channelIt->second;
	if (!channel->isOperator(client)) {
		ERR_CHANOPRIVSNEEDED(*client, channel);
		return ;
	}
	else if (!channel->isMember(clientNick)) {
		ERR_USERNOTINCHANNEL(*client, channel);
		return ;
	}
	else if (!(channel->isMember(client))) {
		ERR_NOTONCHANNEL(*client, channel);
		return ;
	}

	channel->sendMessage(Client::getClientID(*client) + " KICK " + channel->getName() + " " + clientNick + + " :" + cmd.getContent());
	channel->removeClient(cmd.getParameters().at(1));
	channel->listClients();
}
