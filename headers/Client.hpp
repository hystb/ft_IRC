#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <global.hpp>

class Server;
class Client
{
	public:
		Client(const std::string& username, int socket, Server& server);
		~Client(void);

		/* getters */
		std::string	getUsername(void) const;
		int getSocket(void) const;
		bool isPassWordUnlocked(void) const;
		bool isConnected(void) const;
		Server& getServer(void) const;

		/* setters */
		void setPassordUnlocked(bool value);
		void setUserConnected(bool value);

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
		Server		&_server;
		//- les chanels dont il est membre ? tab de string avec les noms des chanels, en map?
};


#endif
