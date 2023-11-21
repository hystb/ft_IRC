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
		std::cerr << Server::getServerLog() << RED <<  "Bad usage ! ./ircserv <port> <password>" << RESET << std::endl;
	else
	{
		if (checkPort(argv[1]) == -1)
			return (std::cout << Server::getServerLog() << RED << "Error in port syntax (0 - 65 535) !" << RESET << std::endl, 1);
		if (checkPort(argv[1]) < 1025)
			std::cout << YELLOW << "Warning ! This port might be reserved to a root access !" << RESET << std::endl;
		try {
			std::map<int, Client*> 	clients;
			std::string				password = argv[2];

			CommandHandler commandHandler = CommandHandler(password);
			Server server = Server(checkPort(argv[1]), password, commandHandler, clients);
		} catch (std::exception &e) {
			// perror("la : ");// faudra supprimer ça batard
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
