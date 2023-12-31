/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:55 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/04 14:45:19 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

# include <map>
# include <Client.hpp>
# include <Channel.hpp>
# include <exception>

class Client;
class Channel;

class Command
{
private:
	std::string 						_input;
	std::string 						_command;
	std::vector<std::string>			_parameters;
	std::string							_content;
	Client* 							_client;
	std::map<std::string, Channel*>&	_channels;
	std::map<int, Client*>&				_clients;

	void parse(void);
	
public:
	/* canonical form */
	~Command(void);

	/* constructor */
	Command(std::string input, Client *client, std::map<std::string, Channel*>& channels, std::map<int, Client*>& clients);

	/* getters */
	const std::string&			 		getInput(void) const;
	const std::string& 					getCommand(void) const;
	const std::vector<std::string>& 	getParameters(void) const;
	std::string							getContent(void) const;

	std::map<std::string, Channel*>&	getChannels(void);
	std::map<int, Client*>&				getClients(void);
	Client* 							getClient(void);

	/* exceptions */
	class invalidException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Invalid command syntax !"); };
	};
};


#endif
