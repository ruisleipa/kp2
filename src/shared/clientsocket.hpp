#ifndef __CLIENTSOCKET_HPP
#define __CLIENTSOCKET_HPP

#include "socket.hpp"

#include <string>

class ClientSocket : public Socket
{
	public:
		bool open(const std::string& host,int port);

		int read(char* data,int size);
		int write(const char* data,int size);

	protected:
		friend class ServerSocket;
};

#endif // __CLIENTSOCKET_HPP

