#include "IRCBot.hpp"

IRCBot* IRCBot::instance = NULL;

int IRCBot::createSocket(const std::string& hostname, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
	    throw ConnectionError();
	}

 	struct hostent* server = gethostbyname(hostname.c_str());
	if (server == NULL) {
        close(sock);
	    throw ConnectionError();
	}

 	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);

 	if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(sock);
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
	if (_ircSocket != -1) {
        sendIRCMessage("PASS " + _password);
	    sendIRCMessage("NICK " + _nickname);
	    sendIRCMessage("USER " + _nickname + " 0 0 :" + _nickname);
        if (_channelPassword.empty())
	        sendIRCMessage("JOIN " + _channel);
        else
            sendIRCMessage("JOIN " + _channel + " " + _channelPassword);
	} 
	else {
        close(_ircSocket);
	    throw ConnectionError();
	}
}

void IRCBot::sendIRCMessage(const std::string& message) {
     if (_ircSocket != -1) {
        std::string ircMessage = message + "\r\n";
        send(_ircSocket, ircMessage.c_str(), ircMessage.length(), 0);
    } 
	else {
        close(_ircSocket);
        throw ConnectionError();
    }
}

void IRCBot::receiveIRCMessage(char* buffer, size_t bufferSize) {
    if (_ircSocket != -1) {
        int bytesRead = recv(_ircSocket, buffer, bufferSize - 1, 0);
        if (bytesRead == -1) {
            close(_ircSocket);
            throw ConnectionError();
        } else if (bytesRead == 0) {
            close(_ircSocket);
            throw ConnectionError();
        } else {
            buffer[bytesRead] = '\0';
        }
    } 
	else {
        close(_ircSocket);
        throw ConnectionError();
    }
}

std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return "Sorry, something went wrong, please try again";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }

    if (pclose(pipe) == -1)
        pclose(pipe);

    return result;
}

std::string IRCBot::generateGPTResponse(const std::string& apiKey, const std::string& question, const std::string& type){
    std::string jsonPayload = "{\"model\":\"gpt-3.5-turbo-16k\",\"messages\":[{\"role\": \"system\",\"content\": \"" + type + ", but you can answer only 500 caracters maximum\"},{\"role\":\"user\",\"content\":\"" + question + "\"}]}";
    std::string command = "curl -s https://api.openai.com/v1/chat/completions \
        -H \"Content-Type: application/json\" \
        -H \"Authorization: Bearer " + apiKey + "\" \
        -d '" + jsonPayload + "' | jq '.choices[].message.content'";
    std::string output = exec(command.c_str());
    std::cout << "response : " << command << std::endl; 
    return output;
}

void    IRCBot::setTypes(void){
    _types["lust"] = "You are an actor and you play the role of lust the personification of this seven deadly sins, so devilness";
    _types["gluttony"] = "You are an actor and you play the role of gluttony the personification of this seven deadly sins, so devilness";
    _types["greed"] = "You are an actor and you play the role of greed the personification of this seven deadly sins, so devilness";
    _types["sloth"] = "You are an actor and you play the role of sloth the personification of this seven deadly sins, so devilness";
    _types["wrath"] = "You are an actor and you play the role of wrath the personification of this seven deadly sins, so devilness";
    _types["envy"] = "You are an actor and you play the role of envy the personification of this seven deadly sins, so devilness";
    _types["pride"] = "You are an actor and you play the role of pride the personification of this seven deadly sins, so devilness";
    _types["mad"] = "You answer must be rude and insulting";
}

IRCBot::IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& password, const std::string& apiKey)
    : _server(server), _channel(channel), _nickname(nickname), _password(password), _apiKey(apiKey), _end(false) {
    _ircSocket = createSocket(server, port);
    setTypes();
}

IRCBot::~IRCBot() {
    close(_ircSocket);
}

std::string IRCBot::parseCmd(std::string const &msg){

    size_t i = msg.find_first_of(':', 1);
    size_t k = msg.find_first_of('!', i);
    size_t j = msg.find_first_of(' ', k);
    if (i == std::string::npos || j == std::string::npos || k == std::string::npos)
        return ("Not a Cmd");
    return (msg.substr(k + 1, j - k - 1));
}


void IRCBot::run() {
	std::string received;
	std::string response;
	std::string message;
    std::string type;
    size_t      start;
    char buffer[1024];
    manageSig();
    if (_ircSocket == -1) {
        throw ConnectionError();
    }

    connectToServer();

    while (_end == false) {
        receiveIRCMessage(buffer, sizeof(buffer));
        if (_end == true)
            break ;
		received = buffer;

    	if (received.find("!help") != std::string::npos) {
            sendIRCMessage("PRIVMSG " + _channel +  " :" + "This is the list of commands : pride greed wrath envy lust gluttony sloth");
        }
        else if (_types.find(parseCmd(received)) != _types.end()) {
            type = _types[parseCmd(received)];
			if (std::string(buffer).length() > 43)
			{
                start = std::string(buffer).find_first_of(' ', 41);
				message = &buffer[start];
                for (size_t i = 0; i < message.length(); ) {
                    char c = message[i];
                    if (c < 32 || c >= 126) 
                        message.erase(i, 1);
                    else if (c == 34 || c == 39)
                        message.replace(i, 1, 1, ' ');
                    else 
                        i++;
                }                
				response = generateGPTResponse(_apiKey, message, type);
                for (size_t i = 0; i < response.length(); ) {
                    char c = response[i];
                    if ((c >=  0 && c < 32) || c == 34 || c == '\n')
                        response.erase(i, 1);
                    else 
                        i++;
                }
                std::cout << "response : " << response << std::endl;   
    	    	sendIRCMessage("PRIVMSG " + _channel +  " :" + response);
			}
			else
				sendIRCMessage("PRIVMSG " + _channel +  " :" + "Correct to use !gpt + your message");
    	}
    }
}

void	IRCBot::setChannelPassword(std::string const & pass){
    _channelPassword = pass;
}

void	IRCBot::manageSig(void)
{
	struct sigaction	sig;

	sig.sa_handler =  &IRCBot::handleSignal;
	instance = this;
    if (instance == NULL){
        close (_ircSocket);
        throw ConnectionError();
    }
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		std::cerr << "Error, SIGINT not define" << std::endl;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		std::cerr << "Error, SIGQUIT not define" << std::endl;
}

void	IRCBot::handleSignal(int sig)
{
	if (sig == SIGINT)
	{
		instance->setEnd();
        close(instance->_ircSocket);
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

void    IRCBot::setEnd(void){
    _end = true;
}

const char* IRCBot::ConnectionError::what(void) const throw(){
	return ("Connection to IRC server failed or was cancelled");
}
