# include <global.hpp>

void CommandHandler::join(Command& cmd)
{
	//multiple join, list

	std::map<std::string, Channel*>::iterator it;

	it = cmd.getChannels().find(cmd.getParameters().at(0));
	if (it == cmd.getChannels().end())
		cmd.getChannels().insert(std::pair<std::string, Channel*>(cmd.getParameters().at(0), \
		new Channel(cmd.getParameters().at(0), cmd.getParameters().at(1), cmd.getClient())));		//create a server
	else {
		if (cmd.getParameters().at(1) == it->second->getPassword())
			it->second->addClient(cmd.getClient(), 0);												//successfull join
		else
			cmd.getClient()->sendMessage(cmd.getClient()->getUsername() + " " + it->second->getName() + " :Cannot join channel (+k)\n");
	}
	
}
