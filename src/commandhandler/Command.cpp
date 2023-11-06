# include <global.hpp>

Command::~Command(void) {}

const std::string&			 	Command::getInput(void) const {
	return (_input);
}

const std::string& 				Command::getCommand(void) const {
	return (_command);
}

const std::vector<std::string>& 	Command::getParameters(void) const {
	return (_parameters);
}

const std::string&				Command::getContent(void) const {
	return (_content);
}

std::map<std::string, Channel*>& Command::getChannels(void) {
	return (_channels);
}

Client* Command::getClient(void) {
	return (_client);
}

void Command::parse(void) 
{
	size_t i, j = 0;
	std::string element = _input.substr(0, _input.length() - 1); // to remove \n
	
	i = element.find_first_of(" ");
	if (i == std::string::npos)
		throw (invalidException());
	_command = element.substr(0, i);
	element = element.substr(i + 1, element.length());
	
	j = element.find_last_of(":");
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

Command::Command(std::string input, Client *client, std::map<std::string, Channel*>& channels) : _input(input), _client(client), _channels(channels)
{
	_command = "\0";
	_content = "\0";
	parse();
}
