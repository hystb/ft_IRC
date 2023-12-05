/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:16 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/05 10:45:51 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
# define LOG_HPP

# include <Client.hpp>
# include <Channel.hpp>

class Client;
class Channel;

void RPL_WELCOME(const Client &client);
void RPL_YOURHOST(const Client &client);
void RPL_CREATED(const Client &client);
void RPL_MYINFO(const Client &client);
void RPL_ISUPPORT(const Client &client);
void RPL_CHANNELMODEIS(const Client &client, const Channel *channel);
void RPL_TOPIC(const Client &client, const Channel *channel);
void RPL_INVITING(const Client &client, const Client &invited, const Channel *channel);
void RPL_NAMREPLY(const Client &client, Channel *channel);
void RPL_ENDOFNAMES(const Client &client, const Channel *channel);
void RPL_MOTDSTART(const Client &client);
void RPL_MOTD(const Client &client, std::string motd);
void RPL_ENDOFMOTD(const Client &client);
void RPL_YOUREOPER(const Client &client);

void ERR_NOSUCHNICK(const Client &client, std::string nick);
void ERR_NOSUCHCHANNEL(const Client &client, std::string channel);
void ERR_NOSUCHCHANNEL(const Client &client, const std::string channelName);
void ERR_CANNOTSENDTOCHAN(const Client &client, std::string target);
void ERR_NOTEXTTOSEND(const Client &client);
void ERR_UNKNOWNCOMMAND(const Client &client);
void ERR_NONICKNAMEGIVEN(const Client &client);
void ERR_ERRONEUSNICKNAME(const Client &client, std::string nick);
void ERR_NICKNAMEINUSE(const Client &client, std::string nick);
void ERR_USERNOTINCHANNEL(const Client &client, const Channel *channel);
void ERR_NOTONCHANNEL(const Client &client, const Channel *channel);
void ERR_USERONCHANNEL(const Client &client, const Channel *channel);
void ERR_NOTREGISTERED(const Client &client);
void ERR_NEEDMOREPARAMS(const Client &client, std::string commandName);
void ERR_ALREADYREGISTERED(const Client &client);
void ERR_PASSWDMISMATCH(const Client &client);
void ERR_CHANNELISFULL(const Client &client, const Channel *channel);
void ERR_INVITEONLYCHAN(const Client &client, const Channel *channel);
void ERR_BADCHANNELKEY(const Client &client, const Channel *channel);
void ERR_CHANOPRIVSNEEDED(const Client &client, const Channel *channel);

void LOG_JOIN(const Client &client, const Channel *channel);
void LOG_INVITE(const Client &invitedClient, const Client &invitingClient, const Channel *channel);
void LOG_KICK(const Client &client, Channel *channel, std::string clientNick, std::string content);
void LOG_MODE_OPERATOR(const Channel *channel, const Client &client, const Client &target, char action, char symbol);
void LOG_MODE_OTHERS(const Channel *channel, const Client &client, char action, char symbol);
void LOG_MODE_ADD_PASSWORD(const Channel *channel, const Client &client, char action, char symbol, std::string key);
void LOG_MODE_LIMIT(const Channel *channel, const Client &client, char action, char symbol, unsigned long limit);

#endif 