# include <global.hpp>

void CommandHandler::topic(Command& cmd)
{
	std::vector<std::string> 	param = cmd.getParameters();
	Client					 	*client = cmd.getClient();
	std::string					content = cmd.getContent();
	std::string					channelName;

	if (param.size() != 1)
		return (ERR_NEEDMOREPARAMS(*client, cmd.getCommand()));
	channelName = param.at(0);
	if (cmd.getChannels().find(channelName) != cmd.getChannels().end())
	{
		// Channel* channel = cmd.getChannels().find(channelName)->second;
		// if (channel->isMember(client)) {
		// 	if (channel.is)
		// }
		// else
		// 	return (ERR_NOTONCHANNEL(*client, channel));
	}
	else
		return (ERR_NOSUCHCHANNEL(*client, channelName));
}