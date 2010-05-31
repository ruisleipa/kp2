#ifndef __SOCKET_HPP
#define __SOCKET_HPP

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <vector>

class SocketSet;

class Socket
{
	public:
		void close();
	
		Socket();
		virtual ~Socket();

	protected:
		int getAddresses(const char* host,int port);
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

