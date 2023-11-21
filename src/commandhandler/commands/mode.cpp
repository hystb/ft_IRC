# include <global.hpp>

void CommandHandler::mode(Command& cmd)
{

	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					channelName;

	// MODE - Change the channel’s mode:
	// · i: Set/remove Invite-only channel
	// · t: Set/remove the restrictions of the TOPIC command to channel
	// · k: Set/remove the channel key (password)
	// · o: Give/take channel operator privilege
	// · l: Set/remove the user limit to channel

	// std::vector<std::string> 	param = cmd.getParameters();
	// Client					 	*client = cmd.getClient();
	// std::string					channelName;


	if (param.size() == 0)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	channelName = param.at(0);
	if (cmd.getChannels().find(channelName) == cmd.getChannels().end())
		return (ERR_NOSUCHCHANNEL(*client, channelName));
	if (param.size() > 1)
	{

	}
	else
		return ;
}