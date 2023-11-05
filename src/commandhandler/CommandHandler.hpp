#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <iostream>
#include "Command.hpp"

class CommandHandler
{
private:
	void commands(int client, Command &cmd);

	/* unlogged commands */
	void quit(void) const;
	void pass(void) const;
	void nick(void) const;
	void user(void) const;

	/* logged commands */
	void kick(void) const;
	void join(void) const;
	void invite(void) const;
	void topic(void) const;
	void mode(void) const;

public:
	/* canonical form */
	CommandHandler(void);
	~CommandHandler(void);
	CommandHandler& operator=(const CommandHandler& parent);
	CommandHandler(const CommandHandler& parent);

	void handleCommand(int client, std::string input); // a remplacer justement avec les vrais clients !
};
#endif