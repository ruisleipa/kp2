#ifndef NET_SERVERSOCKET_HPP
#define NET_SERVERSOCKET_HPP

#include "socket.hpp"
#include "clientsocket.hpp"

#include <string>

namespace Net
{

class ServerSocket: public Socket
{
	public:
		bool open(const std::string& hostname,int port);
	
		bool accept(ClientSocket& socket);
};

};

#endif
