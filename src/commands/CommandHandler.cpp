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

void CommandHandler::handleCommand(int client, std::string input)
{
	(void) client;
	
	Command cmd = Command(input);
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