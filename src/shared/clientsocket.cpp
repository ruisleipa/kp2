#include "clientsocket.hpp"

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#include <iostream>
#include <errno.h>

#include "socketcore.hpp"

int ClientSocket::open(std::string host,int port)
{
	close();

	getAddresses(host.c_str(),port,false);
	
	addrinfo* p;
	
	while((p=nextAddress()))
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(!isSocketValid())
			continue;
			
		if(connect(m_socket,p->ai_addr,p->ai_addrlen)==SOCKET_ERROR)
		{
			close();
			continue;			
		}
		
#ifdef WIN32		
		unsigned long nonblock=1;
		if(ioctlsocket(m_socket,FIONBIO,&nonblock)==SOCKET_ERROR)		
#else
		int flags=fcntl(m_socket,F_GETFL,0);
		if(fcntl(m_socket,F_SETFL,flags|O_NONBLOCK)==-1)		
#endif
		{
			std::cerr<<"Cannot set socket to non-blocking mode: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			close();
		}
		
		break;
	}
	
	freeAddresses();
	
	if(p==0)
	{
		std::cerr<<"Cannot connect to \""<<host<<"\" port "<<port<<":"<<SocketCore::getInstance().getErrorMessage()<<std::endl;
		return -1;
	}

	return 0;
}

int ClientSocket::read(char* data,int size)
{
	if(!isSocketValid())
		return 0;

	int res=recv(m_socket,data,size,0);
	
	if(res==SOCKET_ERROR)
	{
#ifdef WIN32
		if(WSAGetLastError()!=WSAEWOULDBLOCK)		
#else
		if(errno!=EWOULDBLOCK)	
#endif
		{
			std::cerr<<"Reading from socket failed: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;	
		}
		
		return 0;
	}
	
	if(res==0)
	{
		close();
		return -1;
	}
	
	return res;
}

int ClientSocket::write(const char* data,int size)
{
	if(!isSocketValid())
		return 0;

	int res=send(m_socket,data,size,0);
	
	if(res==SOCKET_ERROR)
	{
#ifdef WIN32
		if(WSAGetLastError()!=WSAEWOULDBLOCK)		
#else
		if(errno!=EWOULDBLOCK)	
#endif
		{
			std::cerr<<"Writing to socket failed: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;	
		}
		
		return 0;
	}
	
	return res;	
}

