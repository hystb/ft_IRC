/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:59 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:54:00 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

# include <log.hpp>
# include <Command.hpp>
# include <map>
# include <Client.hpp>
# include <Channel.hpp>

class Command;

class CommandHandler
{
private:
	void commands(Command &cmd);

	/* unlogged commands */
	void quit(Command& cmd);
	void pass(Command& cmd);
	void nick(Command& cmd);
	void user(Command& cmd);

	/* logged commands */
	void kick(Command& cmd);
	void join(Command& cmd);
	void invite(Command& cmd);
	void topic(Command& cmd);
	void mode(Command& cmd);
	void ping(Command& cmd);
	void privmsg(Command& cmd);
	void part(Command& cmd);

	/* vars */
	std::string& 				_pass;

public:
	/* canonical form */
	CommandHandler(std::string &pass);
	~CommandHandler(void);

	void handleCommand(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*> &clients);
};
#endif