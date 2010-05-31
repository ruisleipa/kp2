#ifndef __SOCKET_HPP
#define __SOCKET_HPP

#include <string>

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#endif

#include <vector>

class SocketSet;

class Socket
{
	public:
		void close();
	
		Socket();
		virtual ~Socket();

	protected:
		int getAddresses(const char* host,int port,bool passive);
		addrinfo* nextAddress();
		void freeAddresses();
		bool isSocketValid();

		int m_socket;
		
		std::vector<SocketSet*> m_socket_sets;
		
		friend class SocketSet;
		
	private:
		addrinfo* m_addrs;
		addrinfo* m_curr_addr;
		
};

#endif // __SOCKET_HPP

