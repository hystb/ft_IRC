#ifndef SERVER_HPP
# define SERVER_HPP

# include <global.hpp>

# define MAX_CLIENTS 1000
# define NETWORK_NAME "Team Rocket"
# define SERVER_NAME "ft_irc"
# define SERVER_VERSION "1.0"
# define RULES_NICKLEN "10"
# define RULES_CHANELLEN "50"
# define RULES_TOPICLEN "200"

class Server
{
	private:
		/* user input */
		uint16_t 						_port;
		std::string 					_password;

		/* other private var(s)*/
		struct sockaddr_in 				_sockaddr;
		struct pollfd					_clients_fd[MAX_CLIENTS + 1];
		int								_clients_nb;
		int								_fd_sock;
		CommandHandler&					_commandHandler;
		std::map<int, Client*>&			_clients;
		std::map<std::string, Channel*>	_channels;
		bool							_end;

		/* startup functions ! */
		void prepare(void);

		void handleClientDeconnection(int index, int type);
		void sendMessage(int client, std::string message);

		/* exit and errors functions */
		void closeFds(void);
		void interrupt(void);
		void cleanChannels(void);
		void cleanClients(void);

		/* tools functions */
		int 	getRawEntry(Client* client);
		int		extractEntry(std::string del, std::string& dest, Client* client);

	public:

		static Server* instance; 

		Server(uint16_t port, std::string password, CommandHandler& cmd_handler, std::map<int, Client*>& clients);	

		~Server(void);

		void start(void);
		void disconnectClient(int index);

		static std::string getServerLog(void);

		void	SetEnd(void);

		static void	handleSignal(int sig);

		void	manageSig(void);

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
