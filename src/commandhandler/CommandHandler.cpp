#include "CommandHandler.hpp"

CommandHandler::CommandHandler(void)
{
}

CommandHandler::~CommandHandler(void)
{
}

CommandHandler::CommandHandler(const CommandHandler& parent)
{
	(*this) = parent;
}

CommandHandler& CommandHandler::operator=(const CommandHandler& parent)
{
	(void) parent;
	// do something here;
	return (*this);
}

// void CommandHandler::loggedCommands(int client, Command &cmd)
// void CommandHandler::unloggedCommands(int client, Command &cmd)

void CommandHandler::handleCommand(int client, std::string input)
{
	(void) client;
	int i = 0;
	std::string	commands[4] = {"INVITE", "JOIN", "KICK", "TOPIC"};
	void (CommandHandler::*functions[4])() const = {&CommandHandler::invite, &CommandHandler::join, &CommandHandler::kick, &CommandHandler::topic};
	Command cmd = Command(input);

	while (commands[i] != cmd.getCommand() && i < 4)
		i++;
	switch (i)
	{
	case 0:
		/* code */
		break;
	case 4:
		// throw (); veut dire que la commande n'est pas reconnue
		break;
	}
	
	// if (client.state == validate ) a implementer quand on la classe

	// debug only
	std::cout << "input : " << cmd.getInput();
	std::cout << "command : " << cmd.getCommand() << std::endl;
	std::cout << "parameters : ";
	for (int i = 0; i < cmd.getParameters().size(); i++)
	{
		std::cout << cmd.getParameters().at(i);
		if (i + 1 < cmd.getParameters().size())
			std::cout << ", ";
	}
	std::cout << std::endl;
	std::cout << "content : " << cmd.getContent() << std::endl;
}