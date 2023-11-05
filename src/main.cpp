#include <iostream>
#include "network/Server.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 3)
		std::cerr << "Bad usage ! ./ircserv <port> <password>" << std::endl;
	else
	{
		try {
			Server server = Server(atoi(argv[1]), argv[2]);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
