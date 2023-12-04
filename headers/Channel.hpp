/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:47 by ebillon           #+#    #+#             */
/*   Updated: 2023/12/04 20:32:19 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <vector>
# include <map>
# include <iostream>
# include <Client.hpp>
# include <config.hpp>
# include <log.hpp>

class Client;

class Channel {
	public:
		Channel(const std::string& name, Client *client);
		~Channel(void);

		// clients map
		void	addClient(Client *client, bool isOperator);
		int		removeClient(Client *client, std::map<std::string, Channel*>& channel_map);
		void	setOperator(Client *client);
		void	unsetOperator(Client *client);
		
		// invited vector
		void	addInvited(Client *client);
		void	removeInvited(const std::string& nickname);
		
		// setters
		void	setPassword(const std::string& password);
		void	setLimit(unsigned long limit);
		void	setInviteOnlyMode(void);
		void	unsetInviteOnlyMode(void);
		void	setTopicRestriction(void);
		void	unsetTopicRestriction(void);
		void	setTopic(const std::string& topic);

		// getters
		std::string					getName(void) const;
		std::string					getPassword(void) const;
		std::string					getTopic(void) const;
		unsigned long				getLimit(void) const;
		std::string					getModes(void) const;
		std::map<Client*, bool>& 	getClients(void);

		bool	isInviteOnlyMode(void) const;
		bool 	isTopicRestriction(void) const;
		bool 	isMember(Client *client);
		bool 	isMember(const std::string &nickname);
		bool	isOperator(Client *client);
		bool	isInvited(const std::string& nickname);

		// attributes
		void		sendMessage(std::string message);
		void		sendMessageWithoutClient(std::string message, Client* without);
		void 		actualiseClientsList(void);
		void		actualiseMode(const Client &target, char action, char symbol);
		std::string listClients(void);

	private:
		std::string 			_name;
		std::string 			_topic;
		std::string				_password;
		unsigned long			_limit;
		bool					_inviteOnlyMode;
		bool					_topicRestriction;
		std::vector<Client*>	_invited;
		std::map<Client*, bool>	_clients;
};

#endif
