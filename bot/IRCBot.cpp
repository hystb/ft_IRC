#include "IRCBot.hpp"

int IRCBot::createSocket(const std::string& hostname, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
	    throw ConnectionError();
	}

 	struct hostent* server = gethostbyname(hostname.c_str());
	if (server == NULL) {
	    throw ConnectionError();
	}

 	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);

 	if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
	    throw ConnectionError();
}

return sock;
}

template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void IRCBot::connectToServer() {
	const std::string serverAddress = _server + ":" + to_string(_port);

	if (_ircSocket != -1) {
	    sendIRCMessage("NICK " + _nickname);
	    sendIRCMessage("USER " + _nickname + " 0 0 :" + _nickname);
        sendIRCMessage("PASS " + _password);
	    sendIRCMessage("JOIN " + _channel);
	} 
	else {
	    throw ConnectionError();
	}
}

void IRCBot::sendIRCMessage(const std::string& message) {
     if (_ircSocket != -1) {
        std::string ircMessage = message + "\r\n";
        send(_ircSocket, ircMessage.c_str(), ircMessage.length(), 0);
    } 
	else 
	{
        throw ConnectionError();
    }
}

void IRCBot::receiveIRCMessage(char* buffer, size_t bufferSize) {
    if (_ircSocket != -1) {
        int bytesRead = recv(_ircSocket, buffer, bufferSize - 1, 0);
        if (bytesRead == -1) {
            throw ConnectionError();
        } else if (bytesRead == 0) {
            throw ConnectionError();
        } else {
            buffer[bytesRead] = '\0';
        }
    } 
	else {
        throw ConnectionError();
    }
}

static FILE* popen98(const char* command, const char* mode) {
    return popen(command, mode);
}

static void pclose98(FILE* stream) {
    pclose(stream);
}

std::string exec(const char* cmd) {
    FILE* pipe = popen98(cmd, "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return "";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        std::cout << result << std::endl;
        result += buffer;
    }

    pclose98(pipe);

    return result;
}

std::string IRCBot::generateGPTResponse(const std::string& apiKey, const std::string& question){
    std::string jsonPayload = "{\"model\":\"gpt-3.5-turbo-16k\",\"messages\":[{\"role\":\"user\",\"content\":\"" + question + "\"}]}";
    std::string command = "curl -s https://api.openai.com/v1/chat/completions \
        -H \"Content-Type: application/json\" \
        -H \"Authorization: Bearer " + apiKey + "\" \
        -d '" + jsonPayload + "' | jq '.choices[].message.content'";
    std::string output = exec(command.c_str());
    std::cout << "output : " << output << std::endl; 
    return output;
}

IRCBot::IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& password, const std::string& apiKey)
    : _server(server), _port(port), _channel(channel), _nickname(nickname), _password(password), _apiKey(apiKey) {
    _ircSocket = createSocket(server, port);
}

IRCBot::~IRCBot() {
    close(_ircSocket);
}

void IRCBot::run() {
	std::string received;
	std::string response;
	std::string message;
    int         i;
    char buffer[1024];
    if (_ircSocket == -1) {
        throw ConnectionError();
    }

    connectToServer();

    while (true) {
        receiveIRCMessage(buffer, sizeof(buffer));
		received = buffer;

    	if (received.find("!gpt") != std::string::npos) {
			if (std::string(buffer).length() > 43)
			{
				message = &buffer[41];
                for (size_t i = 0; i < message.length(); ) {
                    char c = message[i];
                    if (c < 32 || c >= 126) 
                        message.erase(i, 1);
                    else if (c == 34 || c == 39)
                        message.replace(i, 1, 1, ' ');
                    else 
                        i++;
                }                
				response = generateGPTResponse(_apiKey, message);
                std::cout << "response : " << response << std::endl;
                for (size_t i = 0; i < response.length(); ) {
                    char c = response[i];
                    if ((c >=  0 && c < 32) || c == 34)
                    { 
                        std::cout << static_cast<int> (response[i]) << response[i] << std::endl;
                        response.erase(i, 1);
                    }
                    else 
                        i++;
                }
                std::cout << "response : " << response << std::endl;   
    	    	sendIRCMessage("PRIVMSG " + _channel +  " :" + response);
			}
			else
				sendIRCMessage("PRIVMSG #help :Correct to use !gpt + your message");
    	}
    }
}

const char* IRCBot::ConnectionError::what(void) const throw(){
			return ("Connection to IRC server failed or was cancelled\0");
}
