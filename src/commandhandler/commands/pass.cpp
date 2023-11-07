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

	if (client->isPassWordUnlocked())
		return (client->sendMessage(client->getNickname() + " :You may not reregister\r\n"));
	if (param.size() == 0)
		refuseConnection(client, "Client PASS :Not enough parameters\r\n");
	else if (param.at(0) != _pass)
		refuseConnection(client, "Client :Password incorrect\r\n");
	else
	{
		client->setPassordUnlocked(1);
	}
}