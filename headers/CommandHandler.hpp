#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

# include <global.hpp>

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

public:
	/* canonical form */
	CommandHandler(void);
	~CommandHandler(void);
	CommandHandler& operator=(const CommandHandler& parent);
	CommandHandler(const CommandHandler& parent);

	void handleCommand(std::string input, Client *client, std::map<std::string, Channel*> channels);
};
#endif