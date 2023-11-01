#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <cstring>
# include <exception>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <unistd.h>
# include <string>
# include <sstream>
# include <vector>
# include <curl/curl.h>

class IRCBot{
	private:
		std::string _apiKey;
	    std::string _server;
	    int16_t 	_port;
	    std::string _channel;
	    std::string _nickname;
	    std::string _apiEndpoint;
	    int 		_ircSocket;

	    int createSocket(const std::string& hostname);
	    void connectToServer();
	    void sendIRCMessage(const std::string& message);
	    void receiveIRCMessage(char* buffer, size_t bufferSize);
		std::string generateGPTResponse(const std::string& apiKey, const std::string& message);
	public :
		IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& apiEndpoint);
		class ConnectionError : public std::exception{
		public:
			virtual const char* what() const throw();
		};
    	~IRCBot();
    	void run();
};

#endif
