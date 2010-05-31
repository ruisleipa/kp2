#ifndef __SOCKETSET_HPP
#define __SOCKETSET_HPP

#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 

#endif

#include <map>

#include "socket.hpp"

class SocketSet
{
	public:
		void add(Socket* socket);
		void remove(Socket* socket);
		
		Socket* waitForActivity();

		SocketSet();
		~SocketSet();
		
	private:
		std::map<int,Socket*> m_sockets;
		int m_highest_fd;		
		fd_set m_fd_set;
		
		int m_current_active;
		fd_set m_active_sockets;
		bool m_first_wait;
};

#endif // __SOCKETSET_HPP

