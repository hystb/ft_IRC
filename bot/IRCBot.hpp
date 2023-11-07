#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <cstring>
# include <exception>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <sstream>
# include <algorithm>
# include <cstdio>

class IRCBot{
	private:
		std::string _apiKey;
	    std::string _server;
	    uint16_t 	_port;
	    std::string _channel;
	    std::string _nickname;
	    int 		_ircSocket;
		std::string _password;

	    int createSocket(const std::string& hostname, int port);
	    void connectToServer();
	    void sendIRCMessage(const std::string& message);
	    void receiveIRCMessage(char* buffer, size_t bufferSize);
		std::string generateGPTResponse(const std::string& apiKey, const std::string& question);
	public :
		IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& password, const std::string& apiKey);
		class ConnectionError : public std::exception{
		public:
			virtual const char* what() const throw();
		};
    	~IRCBot();
    	void run();
};

template <typename T>
std::string to_string(const T& value);

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
#endif
