#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <global.hpp>

class Client
{
	public:
		Client(const std::string& username, int socket);
		~Client(void);
		Client& operator=(const Client &parent);
		Client(const Client &parent);

		/* getters */
		std::string	getUsername(void) const;
		int getSocket(void) const;
		bool isPassWordUnlocked(void) const;
		bool isConnected(void) const;

		/* attributes */
		void sendMessage(std::string message) const;
		std::string& getBuffer(void);
	private:
		Client(void);

		std::string	_username;
		int			_socketFd;
		bool		_passwordUnlocked;
		bool		_userConnected;//status de la requete au serveur, utilisateur validé ou pas?
		
		std::string _buffer;
		//- les chanels dont il est membre ? tab de string avec les noms des chanels, en map?
};

#endif
