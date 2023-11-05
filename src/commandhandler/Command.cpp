#include "Command.hpp"

Command::Command(void) {}

Command::Command(const Command &parent)
{
	(*this) = parent;
}

Command& Command::operator=(const Command &parent)
{
	(void) parent;
	//do something here;
	return (*this);
}

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

Command::Command(std::string input) : _input(input)
{
	_command = "\0";
	_content = "\0";
	parse();
}
