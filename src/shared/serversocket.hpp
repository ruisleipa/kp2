#ifndef __SERVERSOCKET_HPP
#define __SERVERSOCKET_HPP

#include "socket.hpp"
#include "clientsocket.hpp"

#include <string>

class ServerSocket: public Socket
{
	public:
		bool open(const std::string& hostname,int port);
	
		bool accept(ClientSocket& socket);
};

#endif // __SERVERSOCKET_HPP
