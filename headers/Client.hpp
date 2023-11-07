#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <global.hpp>

class Server;
class Channel;
class Client
{
	public:
		Client(const std::string& username, int socket, Server& server);
		~Client(void);

		/* getters */
		std::string getNickname(void) const;
		int getSocket(void) const;
		bool isPassWordUnlocked(void) const;
		bool isConnected(void) const;
		Server& getServer(void) const;
		std::string getUsername(void) const;

		/* setters */
		void setPassordUnlocked(bool value);
		void setUserConnected(bool value);
		void setNickname(std::string& name);
		void setUsername(std::string& username);

		/* attributes */
		void sendMessage(std::string message) const;
		std::string& getBuffer(void);

		static void broadcastFromClient(std::map<std::string, Channel*>& channels, Client* targetClient, std::string content);
		
	private:
		Client(void);

		std::string	_nickname;
		std::string _username;
		int			_socketFd;
		bool		_passwordUnlocked;
		bool		_userConnected;//status de la requete au serveur, utilisateur validé ou pas?
		
		std::string _buffer;
		Server		&_server;
		//- les chanels dont il est membre ? tab de string avec les noms des chanels, en map?
};

#endif
