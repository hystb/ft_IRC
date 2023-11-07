#include "IRCBot.hpp"

int main(int argc, char const *argv[])
{
	if (argc == 6)
	{	
		size_t size;
		std::string server = argv[1];
    	int port;
		std::istringstream iss(argv[2]);
		iss >> port;
    	const std::string channel = "#" + std::string(argv[3]);
		const std::string password = argv[4];
		const std::string apikey = argv[5];
    	const std::string nickname = "RocketBot";
		try
		{
    		IRCBot bot(server, port, channel, nickname, password, apikey);
    		bot.run();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Args needed as following <Server Address> <Port> <Channel> <Password> <ApiKey> <Channel Password>" << std::endl;
	}
	return 0;
}
