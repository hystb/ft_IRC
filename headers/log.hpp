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
void RPL_CREATIONTIME(const Client &client, const Channel *channel);
void RPL_UMODEIS(const Client &client);
void RPL_TOPIC(const Client &client, const Channel *channel);
void RPL_INVITING(const Client &client, const Channel *channel);
void RPL_NAMREPLY(const Client &client, Channel *channel);
void RPL_ENDOFNAMES(const Client &client, const Channel *channel);
void RPL_MOTDSTART(const Client &client);
void RPL_MOTD(const Client &client, std::string motd);
void RPL_ENDOFMOTD(const Client &client);

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
void ERR_UMODEUNKNOWNFLAG(const Client &client);

void LOG_JOIN(const Client &client, const Channel *channel);

#endif 