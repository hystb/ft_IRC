# include <global.hpp>

void CommandHandler::nick(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					nickname;

	if (param.size() == 0)
		return (client->sendMessage(client->getNickname() + " :No nickname given\r\n"));
	nickname = param.at(0);
	if (nickname == "undefined")
		return (client->sendMessage(client->getNickname() + " :Forbidden nickname\r\n"));
	for (std::map<int, Client*>::iterator it = cmd.getClients().begin(); it != cmd.getClients().end(); it++)
	{
		if (nickname == it->second->getNickname())
			return (client->sendMessage(client->getNickname() + " " + nickname + " :Nickname is already in use\r\n"));
	}
	if (client->getNickname() == "undefined")
		client->sendMessage("NICK " + nickname + "\r\n");
	else
	{
		client->sendMessage(":" + client->getNickname() + " NICK " + nickname +"\r\n");
		Client::broadcastFromClient(cmd.getChannels(), client, ":" + client->getNickname() + " NICK " + nickname + "\r\n");
	}
	client->setNickname(nickname);
	client->doLogin();
}