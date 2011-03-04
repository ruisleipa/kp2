#include "socketset.hpp"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <errno.h>
#include <stdlib.h>

#include "utils/string.hpp"
#include "debug/assert.hpp"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

static std::string getErrorMessage()
{
	std::string msg;

#ifdef WIN32	
	LPSTR err=NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0,WSAGetLastError(),0,(LPSTR)&err,0,0);	
	msg=err;	
	LocalFree(err);
#else
	msg=strerror(errno);
#endif

	return msg;   
}

void SocketSet::add(Socket* socket)
{
	m_sockets.insert(socket);
	
	socket->m_socket_sets.insert(this);
}

void SocketSet::remove(Socket* socket)
{
	m_sockets.erase(socket);
	
	socket->m_socket_sets.erase(this);
	
	std::vector<Socket*>::iterator i;
	
	for(i=m_writable_sockets.begin();i!=m_writable_sockets.end();++i)
	{
		if((*i) == socket)
		{
			m_writable_sockets.erase(i);
			break;
		}
	}
	
	for(i=m_readable_sockets.begin();i!=m_readable_sockets.end();++i)
	{
		if((*i) == socket)
		{
			m_readable_sockets.erase(i);
			break;
		}
	}
}

void SocketSet::socketClosed(Socket* socket)
{
	std::vector<Socket*>::iterator i;
	
	for(i=m_writable_sockets.begin();i!=m_writable_sockets.end();++i)
	{
		if((*i) == socket)
		{
			m_writable_sockets.erase(i);
			break;
		}
	}
	
	for(i=m_readable_sockets.begin();i!=m_readable_sockets.end();++i)
	{
		if((*i) == socket)
		{
			m_readable_sockets.erase(i);
			break;
		}
	}
}

SocketActivity SocketSet::waitForActivity()
{
	if(m_readable_sockets.size() > 0)
	{		
		if(m_writable_sockets.size() > 0)
		{
			Socket* socket=m_writable_sockets.back();
			m_writable_sockets.pop_back();
			
			if(socket->isWritePending())
				socket->commitWrite();
		}
		
		Socket* socket=m_readable_sockets.back();
		m_readable_sockets.pop_back();
		
		return SocketActivity(socket,true,false);
	}
	
	while(m_writable_sockets.size() > 0)
	{
		Socket* socket=m_writable_sockets.back();
		m_writable_sockets.pop_back();
		
		if(socket->isWritePending())
			socket->commitWrite();
	}
	
	if(m_readable_sockets.size() == 0 && m_writable_sockets.size() == 0)
		updateActivity();
	
	return waitForActivity();
}

SocketSet::SocketSet()
{
	
}

SocketSet::~SocketSet()
{
	std::set<Socket*>::iterator i;
	
	for(i=m_sockets.begin();i!=m_sockets.end();++i)
	{
		(*i)->m_socket_sets.erase(this);
	}
}

void SocketSet::updateActivity()
{
	fd_set readable;
	fd_set writable;
	
	std::map<int,Socket*> socket_table;
	
	int nfds=0;

	FD_ZERO(&readable);
	FD_ZERO(&writable);
		
	for(std::set<Socket*>::iterator i=m_sockets.begin();i!=m_sockets.end();++i)
	{
		int socket=(*i)->m_socket;
		
		if(socket == int(INVALID_SOCKET))
			continue;
		
		socket_table[socket]=(*i);
		
		FD_SET(socket, &readable);
	
		if((*i)->isWritePending())
		{
			FD_SET(socket, &writable);
		}
		
		if(socket > nfds)
			nfds = socket;
	}
	
	nfds++;
	
	if(select(nfds,&readable,&writable,0,NULL)==SOCKET_ERROR)
	{
		std::cerr << "select(";
		std::cerr << nfds << ",";
		std::cerr << &readable << ",";
		std::cerr << &writable << ",";
		std::cerr << 0 << ",";
		std::cerr << 0 << ")";
		std::cerr << " failed: " <<getErrorMessage()<<std::endl;
		
		abort();
	}
		
	for(std::map<int,Socket*>::iterator i=socket_table.begin();i!=socket_table.end();++i)
	{
		Socket* socket=(*i).second;
		
		if(socket == 0)
			continue;
	
		if(FD_ISSET((*i).first,&readable))
			m_readable_sockets.push_back(socket);
		
		if(FD_ISSET((*i).first,&writable))
			m_writable_sockets.push_back(socket);
	}
}

