#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <exception>

class Server
{
private:
	/* user input */
	int16_t 	_port;
	std::string _password;

	/* other private var(s)*/
	struct sockaddr_in 	_sockaddr;
	int					fd_sock;

	/* canonical form */
	
	/* private(s) function(s)*/
	void setup(void);
	
public:
	Server(void);
	Server(int16_t port, std::string password);
	Server& operator=(const Server &parent);
	Server(const Server &parent);
	
	~Server(void);

	/* exceptions */
	class initException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error while creating socket !"); };
	};
};

Server::Server(int16_t port, std::string password) : _port(port), _password(password) {
	_sockaddr.sin_port = htons(_port);
	_sockaddr.sin_family = PF_INET;

	try {
		setup();
	} catch (std::exception &e)
	{
		std::cout << "Fatal Error : Server failed to initialized !" << std::endl;
		std::cout << "-> " << e.what() << std::endl;
		throw (e);
	}
}

#endif