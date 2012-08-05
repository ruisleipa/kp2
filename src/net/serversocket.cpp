#include "serversocket.hpp"

namespace Net
{

bool ServerSocket::open(const std::string& hostname,int port)
{
	return bindImpl(hostname,port);
}

bool ServerSocket::accept(ClientSocket& socket)
{
	int newsocket;

	if(acceptImpl(newsocket) == false)
		return false;

	socket.captureSocket(newsocket);

	return true;
}

};
