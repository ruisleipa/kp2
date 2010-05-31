#include "serversocket.hpp"

#include <string.h>
#include <stdio.h>
#include <iostream>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#include "socketcore.hpp"

int ServerSocket::open(int port)
{
	close();

	getAddresses(0,port,true);
	
	addrinfo* p;
	int yes=1;
	
	while((p=nextAddress()))
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(!isSocketValid())
		{
			std::cerr<<"Cannot create socket:"<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			continue;
		}
		
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&yes,sizeof(yes))==SOCKET_ERROR)
		{
			std::cerr<<"Cannot set SO_REUSEADDR:"<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			close();
			continue;
		}
		
		if(bind(m_socket,p->ai_addr,p->ai_addrlen)==SOCKET_ERROR)
		{
			std::cerr<<"Cannot bind to port "<<port<<":"<<SocketCore::getInstance().getErrorMessage()<<std::endl;
			close();
			continue;			
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

void ServerSocket::accept(ClientSocket& socket)
{
	if(!isSocketValid())
		return;

	int newsocket;

	while((newsocket=::accept(m_socket,0,0))==INVALID_SOCKET);
	
	socket.m_socket=newsocket;	
}

