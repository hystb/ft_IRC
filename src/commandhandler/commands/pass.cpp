# include <global.hpp>

void refuseConnection(Client* client, std::string why)
{
	client->sendMessage(why);
	client->getServer().disconnectClient(client->getSocket());
}

void CommandHandler::pass(Command& cmd)
{
	std::vector<std::string> param = cmd.getParameters();
	Client					 *client = cmd.getClient();

	std::cout << "ye sui la" << std::endl;
	if (client->isPassWordUnlocked())
		return (client->sendMessage(client->getUsername() + " :You may not reregister\n"));
	if (param.size() == 0)
		refuseConnection(client, "Client PASS :Not enough parameters\n");
	else if (param.at(0) != _pass)
		refuseConnection(client, "Client :Password incorrect\n");
	else
	{
		client->setPassordUnlocked(1);
	}
}