/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:40 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/05 10:45:45 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <Command.hpp>

void RPL_WELCOME(const Client &client) {
	client.sendMessage(":localhost 001 " + client.getNickname() + " :Welcome to the " + NETWORK_NAME + " Network, " + client.getNickname() + "!" + client.getUsername() + "@localhost");
}

void RPL_YOURHOST(const Client &client) {
	client.sendMessage(":localhost 002 " + client.getNickname() + " :Your host is " + SERVER_NAME + ", running on version " + SERVER_VERSION);
}

void RPL_CREATED(const Client &client) {
	client.sendMessage(":localhost 003 " + client.getNickname() + " :Your server was created 15th october 1996 !");
}

void RPL_MYINFO(const Client &client) {
	client.sendMessage(":localhost 004 " + client.getNickname() + " " + SERVER_NAME + " " + SERVER_VERSION + " o tpkil k,l");
}

void RPL_ISUPPORT(const Client &client) {
	client.sendMessage(":localhost 005 " + client.getNickname() + " NICKLEN=" + RULES_NICKLEN + " CHANNELEN=" + RULES_CHANELLEN + " :are supported by this server");
}

void RPL_CHANNELMODEIS(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 324 " + client.getNickname() + " " + channel->getName() + " " + channel->getModes());
}

void RPL_NOTOPIC(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 331 " + client.getNickname() + " " + channel->getName() + " :No topic is set");
}

void RPL_TOPIC(const Client &client, const Channel *channel) {
	if (channel->getTopic().empty())
		return (RPL_NOTOPIC(client, channel));
	client.sendMessage(":localhost 332 " + client.getNickname() + " " + channel->getName() + " :" + channel->getTopic());
}

void RPL_INVITING(const Client &client, const Client &invited, const Channel *channel) {
	client.sendMessage(":localhost 341 " + client.getNickname() + " " + invited.getNickname() + " " + channel->getName());
}

void RPL_NAMREPLY(const Client &client, Channel *channel) {
	client.sendMessage(":localhost 353 " + client.getNickname()  + " = " + channel->getName() + " :" + channel->listClients());
}

void RPL_ENDOFNAMES(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 366 " + channel->getName() + " :End of /NAMES list");
}

void RPL_MOTD(const Client &client, std::string motd) {
	client.sendMessage(":localhost 372 " + client.getNickname() + " :" + motd);
}

void RPL_MOTDSTART(const Client &client) {
	client.sendMessage(":localhost 375 " + client.getNickname() + " :- " + SERVER_NAME + " Message of the day - ");
}

void RPL_ENDOFMOTD(const Client &client) {
	client.sendMessage(":localhost 376 " + client.getNickname() + " :End of /MOTD command.");
}

void RPL_YOUREOPER(const Client &client) {
	client.sendMessage(":localhost 381 " + client.getNickname() + " :You are now an IRC operator");
}

void ERR_NOSUCHNICK(const Client &client, std::string nick) {
	client.sendMessage(":localhost 401 " + client.getNickname() + " " + nick + " :No such nick");
}

void ERR_NOSUCHCHANNEL(const Client &client, std::string channel) {
	client.sendMessage(":localhost 403 " + client.getNickname() + " " + channel + " :No such channel");
}

void ERR_CANNOTSENDTOCHAN(const Client &client, std::string target) {
	client.sendMessage(":localhost 404 " + client.getNickname() + " " + target + " :Cannot send to channel");
}

void ERR_NOTEXTTOSEND(const Client &client) {
	client.sendMessage(":localhost 412 " + client.getNickname() + " :No text to send");
}

void ERR_UNKNOWNCOMMAND(const Client &client) {
	client.sendMessage(":localhost 421 " + client.getNickname() + " : Unknowm command");
}

void ERR_NONICKNAMEGIVEN(const Client &client) {
	client.sendMessage(":localhost 431 " + client.getNickname() + " :No nickname given");
}

void ERR_ERRONEUSNICKNAME(const Client &client, std::string nick) {
	client.sendMessage(":localhost 432 " + client.getNickname() + " " + nick + " :Erroneus nickname");
}

void ERR_NICKNAMEINUSE(const Client &client, std::string nick) {
	client.sendMessage(":localhost 433 " + client.getNickname() + " " + nick + " :Nickname is already in use");
}

void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 441 " + client.getNickname() + " " + channel->getName() + " :They aren't on that channel");
}

void ERR_NOTONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 442 " + client.getNickname() + " " + channel->getName() + " :You're not on that channel");
}

void ERR_USERONCHANNEL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 443 " + client.getNickname() + " " + client.getNickname() + " " + channel->getName() + " :is already on channel");
}

void ERR_NOTREGISTERED(const Client &client) {
	client.sendMessage(":localhost 451 " + client.getNickname() + " :You have not registered");
}

void ERR_NEEDMOREPARAMS(const Client &client, std::string commandName) {
	client.sendMessage(":localhost 461 " + client.getNickname() + " " + commandName + " :Not enough parameters");
}

void ERR_ALREADYREGISTERED(const Client &client) {
	client.sendMessage(":localhost 462 " + client.getNickname() + " :You may not reregister");
}

void ERR_PASSWDMISMATCH(const Client &client) {
	client.sendMessage(":localhost 464 " + client.getNickname() + " :Password incorrect"); 
}

void ERR_CHANNELISFULL(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 471 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+l)");
}

void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 473 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+i)");
}

void ERR_BADCHANNELKEY(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 475 " + client.getNickname() + " " + channel->getName() + " :Cannot join channel (+k)");
}

void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel) {
	client.sendMessage(":localhost 482 " + client.getNickname() + " " + channel->getName() + " :You're not channel operator");
}

void LOG_JOIN(const Client &client, const Channel *channel) {
	client.sendMessage(Client::getClientID(client) + " JOIN " + channel->getName());
}

void LOG_INVITE(const Client &invitingClient, const Client &invitedClient, const Channel *channel) {
	invitedClient.sendMessage(Client::getClientID(invitingClient) + " INVITE " + invitedClient.getNickname() + " " + channel->getName());
}

void LOG_KICK(const Client &client, Channel *channel, std::string clientNick, std::string content) {
	channel->sendMessage(Client::getClientID(client) + " KICK " + channel->getName() + " " + clientNick + + " :" + content);
}

void LOG_MODE_OPERATOR(const Channel *channel, const Client &client, const Client &target, char action, char symbol) {
	client.sendMessage(Client::getClientID(client) + " MODE " + channel->getName() + " " + action + symbol + " " + target.getNickname());
}

void LOG_MODE_OTHERS(const Channel *channel, const Client &client, char action, char symbol) {
	client.sendMessage(Client::getClientID(client) + " MODE " + channel->getName() + " " + action + symbol);
}

void LOG_MODE_ADD_PASSWORD(const Channel *channel, const Client &client, char action, char symbol, std::string key) {
		client.sendMessage(Client::getClientID(client) +" MODE " + channel->getName() + " " + action + symbol + " " + key);
}

void LOG_MODE_LIMIT(const Channel *channel, const Client &client, char action, char symbol, unsigned long limit) {
	std::stringstream strstream;
	strstream << limit;
	client.sendMessage(Client::getClientID(client) + " MODE " + channel->getName() + " " + action + symbol + " " + strstream.str());
}
