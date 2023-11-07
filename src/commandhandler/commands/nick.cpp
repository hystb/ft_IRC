# include <global.hpp>

void CommandHandler::nick(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					nickname;

	if (param.size() == 0)
		return (client->sendMessage(client->getNickname() + " :No nickname given\n"));
	nickname = param.at(0);
	if (nickname == "undefined")
		return (client->sendMessage(client->getNickname() + " :Forbidden nickname\n"));
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (nickname == it->second->getNickname())
			return (client->sendMessage(client->getNickname() + " " + nickname + " :Nickname is already in use\n"));
	}
	client->setNickname(nickname);
}