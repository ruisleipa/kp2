#ifndef SOCKETSET_HPP
#define SOCKETSET_HPP

#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 

#endif

#include <set>
#include <vector>

#include "socket.hpp"
#include "socketactivity.hpp"

class SocketSet
{
	public:
		void add(Socket* socket);
		void remove(Socket* socket);
			
		SocketActivity waitForActivity(unsigned int timeOutInMilliseconds = 0);

		SocketSet();
		~SocketSet();
		
	private:
		SocketSet(const SocketSet&);
		SocketSet& operator=(const SocketSet&);
	
		void updateActivity(unsigned int timeOutInMilliseconds);
		void socketClosed(Socket* socket);
	
		std::set<Socket*> sockets;
		std::vector<Socket*> readableSockets;
		std::vector<Socket*> writableSockets;
		
		friend class Socket;
};

#endif // SOCKETSET_HPP

