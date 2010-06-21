#include "serversocket.hpp"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#include "socketcore.hpp"

int ServerSocket::open(const std::string& host,int port)
{
	close();

	getAddresses(host.c_str(),port,true);
	
	addrinfo* p;
	int yes=1;
	
	while((p=nextAddress()))
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(!isSocketValid())
		{
			std::cerr<<"Cannot create socket: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			continue;
		}
		
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&yes,sizeof(yes))==SOCKET_ERROR)
		{
			std::cerr<<"Cannot set SO_REUSEADDR: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			close();
			continue;
		}
		
		if(bind(m_socket,p->ai_addr,p->ai_addrlen)==SOCKET_ERROR)
		{
			std::cerr<<"Cannot bind to port "<<port<<": "<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			close();
			continue;			
		}
		
		/* Set the socket to non blocking mode. */

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
	
	if(p==0)
	{
		return -1;
	}
	
	freeAddresses();
	
	if(listen(m_socket,10)==SOCKET_ERROR)
	{
		std::cerr<<"Cannot listen socket:"<<SocketCore::getInstance().getErrorMessage()<<std::endl;
		close();
		return -1;			
	}	

	return 0;
}

int ServerSocket::accept(ClientSocket& socket)
{
	if(!isSocketValid())
		return -1;

	int newsocket;

	newsocket=::accept(m_socket,0,0);
	
	if(newsocket==INVALID_SOCKET)
	{
#ifdef WIN32
		if(WSAGetLastError()!=WSAEWOULDBLOCK)		
#else
		if(errno!=EWOULDBLOCK)	
#endif
		{
			std::cerr<<"accept failed: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;	
		}
		
		return -1;
	}
	
#ifdef WIN32		
	unsigned long nonblock=1;
	if(ioctlsocket(newsocket,FIONBIO,&nonblock)==SOCKET_ERROR)		
#else
	int flags=fcntl(m_socket,F_GETFL,0);
	if(fcntl(newsocket,F_SETFL,flags|O_NONBLOCK)==-1)		
#endif
	{
		std::cerr<<"Cannot set socket to non-blocking mode: "<<SocketCore::getInstance().getErrorMessage()<<std::endl;
		close();
	}	

	socket.m_socket=newsocket;
	
	return 0;
}

