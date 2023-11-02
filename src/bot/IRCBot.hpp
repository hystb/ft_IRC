#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <string>
# include <cstring>
# include <exception>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <unistd.h>
# include <string>
# include <sstream>
# include <vector>
# include <algorithm>
# include <cstdlib>
# include <cstdio>
# include <memory>

class IRCBot{
	private:
		std::string _apiKey;
	    std::string _server;
	    int16_t 	_port;
	    std::string _channel;
	    std::string _nickname;
	    std::string _apiEndpoint;
	    int 		_ircSocket;
		std::string _password;

	    int createSocket(const std::string& hostname, int port);
	    void connectToServer();
	    void sendIRCMessage(const std::string& message);
	    void receiveIRCMessage(char* buffer, size_t bufferSize);
		std::string generateGPTResponse(const std::string& apiKey, const std::string& question);
	public :
		IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& apiEndpoint, const std::string& password, const std::string& apiKey);
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
