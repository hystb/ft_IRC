//#include <vector>
#include <map>
#include <iostream>
#include "Client.hpp"

class Channel {

	public:
		Channel(const std::string& name) : _name(name) {}
		//need canonical form

		//map
		// void addClient(Client &client) {
		// 	_clients[client.getUsername()] = client.getIsModerator();
		// }

		void removeClient(const std::string& username) {
			for (std::map<Client, bool>::iterator it = _clients.begin(); it != _clients.end(); ) {
				if (it->first.getUsername() == username) {
					_clients.erase(it++);
				} else {
					++it;
				}
			}
		}
		
		void listClients() {
			for (std::map<Client, bool>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
				const Client& client = it->first;
				bool isModerator = it->second;
				std::cout << "Client: " << client.getUsername();
				if (isModerator)
					std::cout << " Moderator" << std::endl;
				else
					std::cout << " Ordinary mortals" << std::endl;
			}
    	}

		// setter???

	private:
		std::string 			_name;
		std::map<Client, bool>	_clients;//0 or 1 if moderator
};
