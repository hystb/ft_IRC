# include <CommandHandler.hpp>

void refuseConnection(Client* client, std::string why, Command& cmd)
{
	if (why == "ARGS")
		ERR_NEEDMOREPARAMS(*client, cmd.getCommand());
	if (why == "FAIL")
		ERR_PASSWDMISMATCH(*client);
	client->setDisconnection(1);
}

void CommandHandler::pass(Command& cmd)
{
	std::vector<std::string> param = cmd.getParameters();
	Client					 *client = cmd.getClient();

	if (client->isPassWordUnlocked())
		return (ERR_ALREADYREGISTERED(*client));
	if (param.size() == 0)
		refuseConnection(client, "ARGS", cmd);
	else if (param.at(0) != _pass)
		refuseConnection(client, "FAIL", cmd);
	else
		client->setPassordUnlocked(1);
}