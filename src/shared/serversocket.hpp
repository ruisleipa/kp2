#ifndef __SERVERSOCKET_HPP
#define __SERVERSOCKET_HPP

#include "clientsocket.hpp"

#include <string>

class ServerSocket : public Socket
{
	public:
		int open(const std::string& host,int port);
	
		int accept(ClientSocket& socket);

};

#endif // __SERVERSOCKET_HPP
