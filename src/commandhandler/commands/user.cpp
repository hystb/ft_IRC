/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:25 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:55:26 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

void CommandHandler::user(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();

	if (client->isConnected())
		return (ERR_ALREADYREGISTERED(*client));
	if (param.size() != 3)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	if (param.at(1) != "0" && param.at(2) != "*")
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	if (cmd.getContent() == "\0")
		client->setRealname(param.at(0));
	else
		client->setRealname(cmd.getContent());
	client->setUsername(param.at(0));
	client->doLogin();
}
