/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:44 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/05 10:34:32 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

int isInvalid(std::string nickname)
{
	if (nickname.find_first_of(": #") != std::string::npos)
		return (1);
	return (0);
}

unsigned long ft_stoi(std::string e)
{
	unsigned long result;

	std::istringstream iss(e);
	iss >> result;

	return (result);
}

void CommandHandler::nick(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					nickname;

	if (param.size() == 0)
		return (ERR_NONICKNAMEGIVEN(*client));
	nickname = param.at(0);
	if (nickname == "undefined" || nickname.length() > ft_stoi(RULES_NICKLEN))
		return (ERR_ERRONEUSNICKNAME(*client, nickname));
	if (isInvalid(nickname))
		return (ERR_ERRONEUSNICKNAME(*client, nickname));
	for (std::map<int, Client*>::iterator it = cmd.getClients().begin(); it != cmd.getClients().end(); it++)
	{
		if (nickname == it->second->getNickname())
			return (ERR_NICKNAMEINUSE(*client, nickname));
	}
	if (client->getNickname() != "undefined")
	{
		client->sendMessage(":" + client->getNickname() + " NICK " + nickname);
		Client::broadcastFromClient(cmd.getChannels(), client, ":" + client->getNickname() + " NICK " + nickname);
		client->setNickname(nickname);
	}
	else
	{
		client->setNickname(nickname);
		client->doLogin();
	}
}
