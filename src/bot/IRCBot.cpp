#include "IRCBot.hpp"

int IRCBot::createSocket(const std::string& hostname) {
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
	serverAddress.sin_port = htons(_port);
	memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);

 	if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
	    throw ConnectionError();
}

return sock;
}

void IRCBot::connectToServer() {
	const std::string serverAddress = _server + ":" + std::to_string(_port);

	if (_ircSocket != -1) {
	    sendIRCMessage("NICK " + _nickname);
	    sendIRCMessage("USER " + _nickname + " 0 0 :" + _nickname);
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

void IRCBot::sendAPIRequest() {
    // Implement sending an API request here
}
std::string IRCBot::generateGPTResponse(const std::string& apiKey, const std::string& message) {
CURL* curl = curl_easy_init();
if (curl) {
    std::ostringstream responseStream;
    std::string url = _apiEndpoint;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string requestBody = "{ \"prompt\": \"" + message + "\", \"max_tokens\": 50 }";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
   // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStream);

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return "Failed to connect to the GPT API.";
    }

    return responseStream.str();
    } 
	else {
        return "Failed to initialize libcurl.";
    }
}

IRCBot::IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& apiEndpoint)
    : _server(server), _port(port), _channel(channel), _nickname(nickname), _apiEndpoint(apiEndpoint) {
    _ircSocket = createSocket(server);
}

IRCBot::~IRCBot() {
    close(_ircSocket);
}

void IRCBot::run() {
	std::string received;
	std::string response;
	std::string message;
    char buffer[1024];
    if (_ircSocket == -1) {
        throw ConnectionError();
    }

    connectToServer();

    while (true) {
        receiveIRCMessage(buffer, sizeof(buffer));
        std::cout << buffer;
		received = buffer;

    	if (received.find("!gpt") != std::string::npos) {
			if (buffer[3])
			{
				message = &buffer[3];
				//response = generateGPTResponse(_apiKey, message);
    	    	//sendIRCMessage(response);
				std::cout << "olala" << std::endl;
			}
			else
				sendIRCMessage("Correct to use : !gpt + your message");
    	}
    }
}
const char* IRCBot::ConnectionError::what(void) const throw(){
			return ("Connection to IRC server failed or was cancelled");
}
