/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:47 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:54:48 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

void CommandHandler::part(Command& cmd) {
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					channelName;
	Channel*					channel;

	if (param.size() < 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	channelName = param.at(0);
	if (cmd.getChannels().find(channelName) == cmd.getChannels().end())
		return (ERR_NOSUCHCHANNEL(*client, channelName));
	channel = cmd.getChannels().find(channelName)->second;
	if (channel->isMember(client))
	{
		channel->sendMessage(Client::getClientID(*client) + " PART " + channelName);
		channel->removeClient(client);
	}
	else
		return (ERR_NOTONCHANNEL(*client, channel));	
}
