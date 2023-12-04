/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:55:30 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/04 14:45:12 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <Command.hpp>

/* contructor & destructor */
Command::Command(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*>& clients) : _input(input), _client(client), _channels(channels), _clients(clients)
{
	_command = "\0";
	_content = "\0";
	parse();
}

Command::~Command(void) {}

/* getters */
const std::string& 					Command::getInput(void) const { return (_input); }
const std::string&  				Command::getCommand(void) const { return (_command); }
const std::vector<std::string>&		Command::getParameters(void) const { return (_parameters); }
std::map<std::string, Channel*>&	Command::getChannels(void) { return (_channels); }
std::map<int, Client*>&				Command::getClients(void) { return (_clients); }
std::string 						Command::getContent(void) const { return (_content); }
Client*								Command::getClient(void) { return (_client); }

/* functions */
void Command::parse(void) 
{
	size_t i, j = 0;
	std::string element = _input.substr(0, _input.length() - 2); // to remove \r\n
	
	i = element.find_first_of(" ");
	if (i == std::string::npos)
	{
		_command = element;
		return ;
	}
	_command = element.substr(0, i);
	element = element.substr(i + 1, element.length());
	
	j = element.find_first_of(":");
	if (j != std::string::npos)
	{
		_content = element.substr(j + 1, element.length() - 1);
		element = element.substr(0, j - 1);
	}
	while (1)
	{
		i = element.find_first_of(" ");
		if (i == 0) {
			element = element.substr(i + 1, element.length());
		}
		else if (i == std::string::npos) {
			if (element.find_first_not_of(" ") != std::string::npos)
				return (_parameters.push_back(element));
			return ;
		}
		else
		{
			_parameters.push_back(element.substr(0, i));
			element = element.substr(i + 1, element.length());
		}
	}
}
