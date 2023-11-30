/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCBot.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/11/30 15:53:38 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <map>
# include <signal.h>
#include <cstdlib>

class IRCBot{
	private:
	    std::string _server;
	    std::string _channel;
	    std::string _nickname;
	    int 		_ircSocket;
		std::string _password;
		std::string _apiKey;
		std::string	_channelPassword;
		std::map<std::string, std::string>	_types;
		bool								_end;

	    int			createSocket(const std::string& hostname, int port);
	    void		connectToServer();
	    void		sendIRCMessage(const std::string& message);
	    void		receiveIRCMessage(char* buffer, size_t bufferSize);
		void		setTypes(void);
		std::string parseCmd(std::string const &msg);
		std::string	generateGPTResponse(const std::string& apiKey, const std::string& question, const std::string& type);
	public :
		static IRCBot* instance;
		static void	handleSignal(int sig);
		IRCBot(const std::string& server, int port, const std::string& channel, const std::string& nickname, const std::string& password, const std::string& apiKey);
		class ConnectionError : public std::exception{
		public:
			virtual const char* what() const throw();
		};
		void	setChannelPassword(std::string const & pass);
		void	manageSig(void);
		void	setEnd(void);
    	~IRCBot();
    	void run();
};

template <typename T>
std::string to_string(const T& value);

#endif
