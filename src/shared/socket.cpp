#include "socket.hpp"

#include <string.h>
#include <iostream>

#include "string.hpp"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#include "socketcore.hpp"

#include "socketset.hpp"

void Socket::close()
{
#ifdef WIN32
	closesocket(m_socket);
#else
	::close(m_socket);
#endif

	std::vector<SocketSet*>::iterator i;
	
	for(i=m_socket_sets.begin();i!=m_socket_sets.end();++i)
	{
		(*i)->remove(this);
	}
	
	m_socket_sets.clear();
	
	m_socket=INVALID_SOCKET;
}

Socket::Socket()
{
	SocketCore::getInstance();

	m_socket=INVALID_SOCKET;
	m_addrs=0;
	m_curr_addr=0;
}

Socket::~Socket()
{
	close();
}

bool Socket::isSocketValid()
{
	return (m_socket!=INVALID_SOCKET);
}

int Socket::getAddresses(const char* host,int port,bool passive)
{
	freeAddresses();
	
	std::string portstring=convertToString(port);
	
	addrinfo hints;
	int status;
	
	memset(&hints,0,sizeof(hints));
	
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	if(passive)
		hints.ai_flags=AI_PASSIVE;	
	hints.ai_protocol=IPPROTO_TCP;
	
	status=getaddrinfo(0,portstring.c_str(),&hints,&m_addrs);
	
	if(status)
	{
		std::cerr<<"getaddrinfo(0,"<<portstring.c_str()<<","<<&hints<<","<<&m_addrs<<") failed: ";
		std::cerr<<gai_strerror(status)<<std::endl;
		
		m_addrs=0;
		
		return -1;
	}

	m_curr_addr=m_addrs;

	return 0;	
}

addrinfo* Socket::nextAddress()
{
	addrinfo* i=m_curr_addr;

	if(m_curr_addr!=0)
		m_curr_addr=m_curr_addr->ai_next;
	
	return i;
}

void Socket::freeAddresses()
{
	if(!m_addrs)
		return;
	
	freeaddrinfo(m_addrs);
	
	m_addrs=0;
	m_curr_addr=0;
}


