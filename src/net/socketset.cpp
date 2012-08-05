#include "socketset.hpp"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <errno.h>
#include <stdlib.h>

#include "utils/string.hpp"

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
/*	LPSTR err=NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0,WSAGetLastError(),0,(LPSTR)&err,0,0);	
	msg=err;	
	LocalFree(err);*/
#else
	msg=strerror(errno);
#endif

	return msg;   
}

namespace Net
{

void SocketSet::add(Socket* socket)
{
	sockets.insert(socket);
	
	socket->m_socket_sets.insert(this);
}

void SocketSet::remove(Socket* socket)
{
	sockets.erase(socket);
	
	socket->m_socket_sets.erase(this);
	
	std::vector<Socket*>::iterator i;
	
	for(i=writableSockets.begin();i!=writableSockets.end();++i)
	{
		if((*i) == socket)
		{
			writableSockets.erase(i);
			break;
		}
	}
	
	for(i=readableSockets.begin();i!=readableSockets.end();++i)
	{
		if((*i) == socket)
		{
			readableSockets.erase(i);
			break;
		}
	}
}

void SocketSet::socketClosed(Socket* socket)
{
	std::vector<Socket*>::iterator i;
	
	for(i=writableSockets.begin();i!=writableSockets.end();++i)
	{
		if((*i) == socket)
		{
			writableSockets.erase(i);
			break;
		}
	}
	
	for(i=readableSockets.begin();i!=readableSockets.end();++i)
	{
		if((*i) == socket)
		{
			readableSockets.erase(i);
			break;
		}
	}
}

SocketActivity SocketSet::waitForActivity(unsigned int timeOutInMilliseconds)
{
	updateActivity(timeOutInMilliseconds);

	while(writableSockets.size() > 0)
	{
		Net::Socket* socket=writableSockets.back();
		writableSockets.pop_back();
		
		Net::SocketActivity activity;
		
		activity.socket = socket;
		activity.canRead = false;
		activity.canWrite = true;
		activity.timeoutExpired = false;
		
		return activity;
	}
	
	if(readableSockets.size() > 0)
	{
		Net::Socket* socket=readableSockets.back();
		readableSockets.pop_back();
		
		Net::SocketActivity activity;
		
		activity.socket = socket;
		activity.canRead = true;
		activity.canWrite = false;
		activity.timeoutExpired = false;
		
		return activity;
	}
	
	SocketActivity activity;
	
	activity.socket = 0;
	activity.canRead = false;
	activity.canWrite = false;
	activity.timeoutExpired = true;
	
	return activity;
}

SocketSet::SocketSet()
{
	
}

SocketSet::~SocketSet()
{
	std::set<Socket*>::iterator i;
	
	for(i=sockets.begin();i!=sockets.end();++i)
	{
		(*i)->m_socket_sets.erase(this);
	}
}

void SocketSet::updateActivity(unsigned int timeOutInMilliseconds)
{
	fd_set readable;
	fd_set writable;
	
	std::map<int,Socket*> socket_table;
	
	int nfds=0;

	FD_ZERO(&readable);
	FD_ZERO(&writable);
		
	for(std::set<Socket*>::iterator i=sockets.begin();i!=sockets.end();++i)
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
	
	timeval* timeout = 0;
	
	timeval val;
	
	if(timeOutInMilliseconds != 0)
	{
		val.tv_sec = timeOutInMilliseconds / 1000;
		val.tv_usec = (timeOutInMilliseconds % 1000) * 1000;
		
		timeout = &val;
	}
	
	if(select(nfds,&readable,&writable,0,timeout)==SOCKET_ERROR)
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
			readableSockets.push_back(socket);
		
		if(FD_ISSET((*i).first,&writable))
			writableSockets.push_back(socket);
	}
}

};
