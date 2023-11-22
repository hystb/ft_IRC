#include <global.hpp>

void CommandHandler::ping(Command& cmd) {
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					token;

	if (param.size() != 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	token = param.at(0);
	return (client->sendMessage(Client::getClientID(*client) + " PONG " + token));
}
