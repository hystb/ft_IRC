#include <global.hpp>

void CommandHandler::privmsg(Command& cmd)
{
	std::vector<std::string> 			param = cmd.getParameters();
	Client					 			*client = cmd.getClient();
	std::map<std::string, Channel*>&	channels = cmd.getChannels();
	std::map<int, Client*>& 			clients = cmd.getClients();
	std::string 						target;

	if (param.size() != 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	if (cmd.getContent() == "\0")
		return (ERR_NOTEXTTOSEND(*client));
	target = param.at(0);
	if (target.find("#") == 0) // mean that it is a channel
	{
		if (channels.find(target) != channels.end())
		{
			std::map<Client*, bool> &clientsInside = channels.find(target)->second->getClients();
			if (clientsInside.find(client) != clientsInside.end()) // mean that he is in the channel
				channels.find(target)->second->sendMessageWithoutClient(Client::getClientID(*client) + " PRIVMSG " + target + " :" + cmd.getContent(), client);
			else
				return (ERR_CANNOTSENDTOCHAN(*client, target));
		}
		else
			return (ERR_NOSUCHCHANNEL(*client, target));
	}
	else {
		for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (it->second->getNickname() == target) {
				it->second->sendMessage(Client::getClientID(*client) + " PRIVMSG " + it->second->getNickname() + " :" + cmd.getContent());
				return ;
			}
		}
		return (ERR_NOSUCHNICK(*client, target));
	}
}