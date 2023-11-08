# include <global.hpp>

void CommandHandler::user(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					username;

	if (client->isConnected())
		return (ERR_ALREADYREGISTERED(*client));
	if (param.size() != 3)
		return ; // ERR_NEEDMOREPARAMS 
	if (param.at(1) != "0" && param.at(2) != "*")
		return ; // ERR_NEEDMOREPARAMS
	if (cmd.getContent() == "\0")
		client->setRealname(param.at(0));
	else
		client->setRealname(cmd.getContent());
	client->setUsername(param.at(0));
	client->doLogin();
}