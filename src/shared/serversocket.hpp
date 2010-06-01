#ifndef __SERVERSOCKET_HPP
#define __SERVERSOCKET_HPP

#include "clientsocket.hpp"

class ServerSocket : public Socket
{
	public:
		int open(int port);
	
		int accept(ClientSocket& socket);

};

#endif // __SERVERSOCKET_HPP
