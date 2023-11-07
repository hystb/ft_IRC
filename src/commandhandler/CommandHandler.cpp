# include <global.hpp>

CommandHandler::CommandHandler(void)
{
}

CommandHandler::CommandHandler(std::string &pass) : _pass(pass)
{
}

CommandHandler::~CommandHandler(void)
{
}

void CommandHandler::setPassword(std::string pass){
	_pass = pass;
}

void CommandHandler::commands(Command &cmd)
{
	// treat all the command about logged users
	int i = 0;
	std::string	commands[8] = {"PASS", "NICK", "USER", "QUIT", "INVITE", "JOIN", "KICK", "TOPIC"};
	void (CommandHandler::*functions[8])(Command& cmd) = {&CommandHandler::pass, &CommandHandler::nick, &CommandHandler::user, &CommandHandler::quit, &CommandHandler::invite, &CommandHandler::join, &CommandHandler::kick, &CommandHandler::topic};

	if (cmd.getCommand() == "CAP")
		return ;
	if (!cmd.getClient()->isConnected() && i > 3)
		return (cmd.getClient()->sendMessage("You must be logged to use that command !"));
	for (int i = 0; i < 8; i++)
	{
		if (commands[i] == cmd.getCommand())
			return ((this->*(functions[i]))(cmd));
	}
}

void CommandHandler::handleCommand(std::string input, Client *client, std::map<std::string, Channel*> channels)
{
	Command cmd = Command(input, client, channels);
	
	commands(cmd);
	// debug only
	// std::cout << "input : " << cmd.getInput();
	// std::cout << "command : " << cmd.getCommand() << std::endl;
	// std::cout << "parameters : ";
	// for (unsigned i = 0; i < cmd.getParameters().size(); i++)
	// {
	// 	std::cout << cmd.getParameters().at(i);
	// 	if (i + 1 < cmd.getParameters().size())
	// 		std::cout << ", ";
	// }
	// std::cout << std::endl;
	// std::cout << "content : " << cmd.getContent() << std::endl;
}