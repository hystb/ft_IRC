#include "IRCBot.hpp"

int main(int argc, char const *argv[])
{
	if (argc == 4)
	{ 
		const std::string server = argv[1];
    	int port;
		std::istringstream iss(argv[2]);
		iss >> port;
    	const std::string channel = argv[3];
    	const std::string nickname = "RocketBot";
    	const std::string apiEndpoint = "https://api.openai.com/v1/engines/davinci/completions";
		try
		{
    		IRCBot bot(server, port, channel, nickname, apiEndpoint);
    		bot.run();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Args needed as following <Server Address> <Port> <Channel>" << std::endl;
	}

    return 0;
}
