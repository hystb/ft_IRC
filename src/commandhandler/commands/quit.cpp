# include <CommandHandler.hpp>

void Client::warnOthersLeaving(Client *client, std::string reason, std::map<std::string, Channel*>& channels)
{
	if (client->isConnected())
		client->broadcastFromClient(channels, client, Client::getClientID(*client) + " QUIT :" + reason);
}

void CommandHandler::quit(Command& cmd)
{
	Client* client = cmd.getClient();
	std::string content = cmd.getContent();
	if (content == "\0")
		content = "";
	client->setDisconnection(1);
	Client::warnOthersLeaving(client, content, cmd.getChannels());
}