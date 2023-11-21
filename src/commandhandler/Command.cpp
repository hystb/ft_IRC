# include <global.hpp>

Command::~Command(void) {}

const std::string&	Command::getInput(void) const {
	return (_input);
}

const std::string& 	Command::getCommand(void) const {
	return (_command);
}

const std::vector<std::string>& Command::getParameters(void) const {
	return (_parameters);
}

std::string Command::getContent(void) const {
	return (_content);
}

std::map<std::string, Channel*>&	Command::getChannels(void) {
	return (_channels);
}

std::map<int, Client*>&	Command::getClients(void) {
	return (_clients);
}

Client*	Command::getClient(void) {
	return (_client);
}

void Command::parse(void) 
{
	size_t i, j = 0;
	std::string element = _input.substr(0, _input.length() - 2); // to remove \n
	
	i = element.find_first_of(" ");
	if (i == std::string::npos)
	{
		_command = element;
		return ;
	}
	_command = element.substr(0, i);
	element = element.substr(i + 1, element.length());
	
	j = element.find_first_of(":");
	if (j != std::string::npos) // mean that there is :trailing ?
	{
		_content = element.substr(j + 1, element.length() - 1);
		element = element.substr(0, j - 1);
	}
	while (1)
	{
		i = element.find_first_of(" ");
		if (i == std::string::npos)
			return (_parameters.push_back(element));
		else
		{
			_parameters.push_back(element.substr(0, i));
			element = element.substr(i + 1, element.length());
		}
	}
}

Command::Command(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*>& clients) : _input(input), _client(client), _channels(channels), _clients(clients)
{
	_command = "\0";
	_content = "\0";
	parse();
}

void Command::listChannel(void) {
	std::cout << "- CHANNEL LIST -" << std::endl;
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		const Channel* channel = it->second;
		std::cout << "Channel: " << channel->getName() << std::endl;
	}
}