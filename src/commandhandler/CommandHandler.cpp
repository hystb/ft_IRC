# include <global.hpp>

CommandHandler::CommandHandler(std::string &pass) : _pass(pass)
{
}

CommandHandler::~CommandHandler(void)
{
}

void CommandHandler::commands(Command &cmd)
{
	std::string	commands[12] = {"PASS", "NICK", "USER", "QUIT", "INVITE", "JOIN", "KICK", "TOPIC", "PING", "PRIVMSG", "PART", "MODE"};
	void (CommandHandler::*functions[12])(Command& cmd) = {&CommandHandler::pass, &CommandHandler::nick, &CommandHandler::user, &CommandHandler::quit, &CommandHandler::invite, &CommandHandler::join, &CommandHandler::kick, &CommandHandler::topic, &CommandHandler::ping, &CommandHandler::privmsg, &CommandHandler::part, &CommandHandler::mode};

	if (cmd.getCommand() == "CAP")
		return ;
	for (int i = 0; i < 12; i++)
	{
		if ((i > 0 && !cmd.getClient()->isPassWordUnlocked()) || (i > 3 && !cmd.getClient()->isConnected()))
			return (ERR_NOTREGISTERED(*cmd.getClient()));
		if (commands[i] == cmd.getCommand())
			return ((this->*(functions[i]))(cmd));
	}
	return (ERR_UNKNOWNCOMMAND(*cmd.getClient()));
}

void CommandHandler::handleCommand(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*> &clients)
{
	Command cmd = Command(input, client, channels, clients);
	std::string toPrint = input.substr(0, input.length() - 2);

	std::cout << Server::getServerLog() << CYAN << "⬅️ " << toPrint << RESET << GRAY << " (" << client->getSocket() << ")" << RESET << std::endl;
	commands(cmd);
}