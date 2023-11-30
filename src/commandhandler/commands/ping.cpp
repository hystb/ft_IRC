/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:55 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:54:56 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandHandler.hpp>

void CommandHandler::ping(Command& cmd) {
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					token;

	if (param.size() != 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	token = param.at(0);
	return (client->sendMessage(Client::getClientID(*client) + " PONG " + token));
}
