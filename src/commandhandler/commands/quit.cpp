/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:17 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:55:18 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

void Client::warnOthersLeaving(Client *client, std::string reason, std::map<std::string, Channel*>& channels)
{
	if (client->isConnected())
		client->broadcastFromClient(channels, client, Client::getClientID(*client) + " QUIT :" + reason);
}

void CommandHandler::quit(Command& cmd)
{
	Client* client = cmd.getClient();
	std::string content = cmd.getContent();
	if (content == "\0")
		content = "";
	client->setDisconnection(1);
	Client::warnOthersLeaving(client, content, cmd.getChannels());
}