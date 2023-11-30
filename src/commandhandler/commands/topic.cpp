/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:21 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 17:39:05 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

void CommandHandler::topic(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					content = cmd.getContent();
	std::string					channelName;

	if (param.size() != 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	channelName = param.at(0);
	if (cmd.getChannels().find(channelName) != cmd.getChannels().end())
	{
		Channel* channel = cmd.getChannels().find(channelName)->second;
		if (channel->isMember(client)) {
			if (content != "\0") {
				if (channel->isTopicRestriction() && !channel->isOperator(client))
					return (ERR_CHANOPRIVSNEEDED(*client, channel));
				else {
					channel->setTopic(content);
					for (std::map<Client*, bool>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); it++)
						RPL_TOPIC(*it->first, channel);
				}
			}
			else
				return (RPL_TOPIC(*client, channel));
		}
		else 
			return (ERR_NOTONCHANNEL(*client, channel));
	}
	else
		return (ERR_NOSUCHCHANNEL(*client, channelName));
}