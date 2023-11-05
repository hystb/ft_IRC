#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <exception> 

#include <stdio.h> // a enlever

#define MAX_CLIENTS 2

class Server
{
private:
	/* user input */
	int16_t 	_port;
	std::string _password;

	/* other private var(s)*/
	struct sockaddr_in 	_sockaddr;
	struct pollfd		_clients_fd[MAX_CLIENTS + 1];
	int					_clients_nb;
	int					_fd_sock;

	/* canonical form */
	Server(void);

	/* startup functions ! */
	void prepare(void);
	void start(void);

	void handleClientDeconnection(int index);
	void sendMessage(int client, std::string message);

	/* exit and errors functions */
	void closeFds(void);
	void interrupt(void);


	/* tools functions */
	int getRawEntry(std::string &buff, int fd, std::string del);
		
	
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

	class initException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error while binding and listening to the socket !"); };
	};

	class crashException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Error during the execution of the server !"); };
	};
};
#endif