#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>

class Server
{
private:
	/* user input */
	int16_t 	_port;
	std::string _password;

	/* other private var(s)*/
	struct sockaddr_in 	_sockaddr;
	int					_fd_sock;

	/* canonical form */
	Server(void);

	/* private(s) function(s)*/
	void prepare(void);
	void start(void);
	
public:
	Server& operator=(const Server &parent);
	Server(const Server &parent);
	Server(int16_t port, std::string password);	
	
	~Server(void);

	/* exceptions */
	class initSocketException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error while creating the socket !"); };
	};

	class initBindException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error while binded the socket !"); };
	};

	class initListenException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error while listening to the socket !"); };
	};
};
#endif