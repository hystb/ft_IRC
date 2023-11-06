#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>

class Client
{
	public:
		Client(const std::string& username, bool isModerator);
		~Client(void);
		Client& operator=(const Client &parent);
		Client(const Client &parent);

		// getter
		std::string	getUsername(void) const;
		bool		getIsModerator(void) const;

	private:
		Client(void);

		std::string	_username;
		bool 		_isModerator;
		int			_socketFd;
		bool		_passwordUnlocked;
		bool		_userConnected;//status de la requete au serveur, utilisateur validé ou pas?
		//- les chanels dont il est membre ? tab de string avec les noms des chanels, en map?
};

#endif
