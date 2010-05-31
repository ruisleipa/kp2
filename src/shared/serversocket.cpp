#include "serversocket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <iostream>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

int ServerSocket::open(int port)
{
	close();

	getAddresses(0,port);
	
	addrinfo* p;
	int yes=1;
	
	while((p=nextAddress()))
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(!isSocketValid())
		{
			perror("socket");
			continue;
		}
		
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes))==-1)
		{
			perror("setsockopt");
			continue;
		}
		
		if(bind(m_socket,p->ai_addr,p->ai_addrlen)==-1)
		{
			perror("bind");
			close();
			continue;			
		}
		
		break;
	}
	
	freeAddresses();
	
	if(listen(m_socket,10)==-1)
	{
		close();
		return -1;			
	}

	if(p==0)
	{
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

