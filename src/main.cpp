#include <global.hpp>

int checkPort(std::string port)
{
	std::stringstream 	ss(port);
	int					value;

	if (port.find_first_not_of("0123456789") != std::string::npos)
		return (-1);
	if (port.length() > 5)
		return (-1);
	ss >> value;
	if (value > 65535)
		return (-1);
	return (value);
}


int main(int argc, char const *argv[])
{
	if (argc != 3)
		std::cerr << "Bad usage ! ./ircserv <port> <password>" << std::endl;
	else
	{
		if (checkPort(argv[1]) == -1)
			return (std::cout << "Error in port syntax (0 - 65 535) !" << std::endl, 1);
		if (checkPort(argv[1]) < 1025)
			std::cout << "Warning ! This port might be reserved to a root access !" << std::endl;
		try {
			Server server = Server(checkPort(argv[1]), argv[2]);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
