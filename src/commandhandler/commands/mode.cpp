# include <global.hpp>

void CommandHandler::mode(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					channelName;

	if (param.size() == 0)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	channelName = param.at(0);
	if (cmd.getChannels().find(channelName) == cmd.getChannels().end())
		return (ERR_NOSUCHCHANNEL(*client, channelName));
	if (param.size() > 1)
	{

	}
	else
		return ();
}