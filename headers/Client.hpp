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

		// getters
		int getSocket(void) const;
		Server& getServer(void) const;
		std::string& getBuffer(void);
		std::string getUsername(void) const;
		std::string getNickname(void) const;
		std::string getRealname(void) const;
		bool isPassWordUnlocked(void) const;
		bool isConnected(void) const;
		bool isToDisconnect(void) const;

		// setters
		void setPassordUnlocked(bool value);
		void setUserConnected(bool value);
		void setDisconnection(bool value);
		void setNickname(std::string& nickname);
		void setUsername(std::string& username);
		void setRealname(std::string  realname);

		// attributes
		void sendMessage(std::string message) const;
		void doLogin(void);

		static void broadcastFromClient(std::map<std::string, Channel*>& channels, Client* targetClient, std::string content);
		static void warnOthersLeaving(Client *client, std::string reason, std::map<std::string, Channel*>& channels);
		static std::string getClientID(const Client &client);
		static Client* getClientFromNickname(std::map<int, Client*>& clients, std::string nickname);
		
	private:
		std::string	_nickname;
		std::string _username;
		std::string _realname;
		int			_socketFd;
		bool		_passwordUnlocked;
		bool		_toDisconnect;
		bool		_userConnected;//status de la requete au serveur, utilisateur validé ou pas?
		
		std::string _buffer;
		Server		&_server;
};

#endif
