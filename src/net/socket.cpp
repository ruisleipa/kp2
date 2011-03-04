#include "socket.hpp"

#include "socketset.hpp"

#include <string.h>
#include <iostream>

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#endif

#include "utils/string.hpp"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifdef WIN32
int Socket::m_winsock_ref_count=0;
#endif

static addrinfo* getAddrInfo(const char* host,int port,bool passive)
{
	std::string portstring=convertToString(port);
	
	addrinfo hints;
	addrinfo* addrs;
	int status;
	
	memset(&hints,0,sizeof(hints));
	
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=IPPROTO_TCP;
	
//	if(passive)
//		hints.ai_flags=AI_PASSIVE;	
	
	status=getaddrinfo(host,portstring.c_str(),&hints,&addrs);
	
	if(status)
	{
		std::cerr<<"getaddrinfo(0,"<<portstring.c_str()<<","<<&hints<<","<<&addrs<<") failed: ";
		std::cerr<<gai_strerror(status)<<std::endl;

		return 0;
	}

	return addrs;
}

static void freeAddrInfo(addrinfo* p)
{
	if(p)
		freeaddrinfo(p);
}

bool Socket::connectImpl(const std::string& hostname,const int port)
{
	close();

	addrinfo* p=getAddrInfo(hostname.c_str(),port,false);
	
	if(!p)
		return false;
		
	std::string errormsg;
	
	for(;p != 0; p = p->ai_next)
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(m_socket == int(INVALID_SOCKET))
			continue;
			
		if(::connect(m_socket,p->ai_addr,p->ai_addrlen) == SOCKET_ERROR)
		{
			errormsg=getErrorMessage();
			close();
			continue;			
		}		
		
		break;
	}
	
	freeAddrInfo(p);
	
	if(!p)
	{
		std::cerr<<"Cannot connect to \""<<hostname<<"\" port "<<port<<": "<<errormsg<<std::endl;
		return false;
	}
	
	if(setNonBlock(m_socket) == false)
	{
		std::cerr<<"Cannot set socket to non-blocking mode: "<<getErrorMessage()<<std::endl;
		close();
	}

	return true;
}

bool Socket::bindImpl(const std::string& hostname,int port)
{
	close();

	addrinfo* p=getAddrInfo(hostname.c_str(),port,false);
	
	for(;p != 0; p = p->ai_next)
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(m_socket == int(INVALID_SOCKET))
		{
			std::cerr<<"Cannot create a socket: "<<getErrorMessage()<<std::endl;
			continue;
		}
		
		int yes=1;
		
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&yes,sizeof(yes))==SOCKET_ERROR)
		{
			std::cerr<<"Cannot set SO_REUSEADDR: "<<getErrorMessage()<<std::endl;
			close();
			continue;
		}
		
		if(::bind(m_socket,p->ai_addr,p->ai_addrlen)==SOCKET_ERROR)
		{
			std::cerr<<"Cannot bind to port "<<port<<": "<<getErrorMessage()<<std::endl;
			close();
			continue;			
		}	
		
		break;
	}
	
	freeAddrInfo(p);
	
	if(!p)
	{
		std::cerr<<"Cannot create a socket: "<<getErrorMessage()<<std::endl;
		return false;
	}
	
	if(listen(m_socket,10)==SOCKET_ERROR)
	{
		std::cerr<<"Cannot listen socket:"<<getErrorMessage()<<std::endl;
		close();
		return false;			
	}
	
	if(setNonBlock(m_socket) == false)
	{
		std::cerr<<"Cannot set socket to non-blocking mode: "<<getErrorMessage()<<std::endl;
		close();
		return false;
	}
		
	return true;
}

bool Socket::acceptImpl(int& socket)
{
	if(m_socket == int(INVALID_SOCKET))
		return false;

	int newsocket;

	newsocket = ::accept(m_socket, 0, 0);
	
	if(newsocket == int(INVALID_SOCKET))
	{
#ifdef WIN32
		if(WSAGetLastError()!=WSAEWOULDBLOCK)		
#else
		if(errno!=EWOULDBLOCK)	
#endif
		{
			std::cerr<<"accept failed: "<<getErrorMessage()<<std::endl;	
		}
		
		return false;
	}
		
	if(setNonBlock(newsocket) == false)
	{
		std::cerr<<"Cannot set socket to non-blocking mode: "<<getErrorMessage()<<std::endl;
		
#ifdef WIN32
		closesocket(newsocket);
#else
		::close(newsocket);
#endif
		
		return false;
	}	

	socket=newsocket;
	
	return true;
}

int Socket::readImpl(char* data,int size)
{
	if(m_socket == int(INVALID_SOCKET))
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
			std::cerr<<"Reading from socket failed: "<<getErrorMessage()<<std::endl;
			close();
			throw ConnectionClosedException();
		}
		
		return 0;
	}
	
	if(res==0)
	{
		close();
		throw ConnectionClosedException();
	}
	
	return res;
}

int Socket::writeImpl(const char* data,int size)
{
	if(m_socket == int(INVALID_SOCKET))
		return 0;

	m_write_buffer.append(data,size);
	
	commitWrite();
	
	return size;	
}

void Socket::close()
{
	if(m_socket != int(INVALID_SOCKET))
#ifdef WIN32
		closesocket(m_socket);
#else
		::close(m_socket);
#endif

	std::set<SocketSet*>::iterator i;
	
	for(i=m_socket_sets.begin();i!=m_socket_sets.end();++i)
	{
		(*i)->socketClosed(this);
	}

	m_socket = INVALID_SOCKET;
}

Socket::Socket():
	m_socket(INVALID_SOCKET)
{
#ifdef WIN32
	m_winsock_ref_count++;

	WSADATA wsaData;
	
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		std::cerr<<"WSAStartup failed:"<<getErrorMessage()<<std::endl;
		exit(1);
	}
#endif
}

Socket::Socket(const Socket& b)
{
	m_socket=b.m_socket;
	b.m_socket=0;
	
	m_write_buffer=b.m_write_buffer;
}

Socket& Socket::operator=(const Socket& b)
{
	m_socket=b.m_socket;
	b.m_socket=0;
	
	m_write_buffer=b.m_write_buffer;
	
	return *this;
}

Socket::~Socket()
{
#ifdef WIN32
	closesocket(m_socket);
#else
	::close(m_socket);
#endif

	std::set<SocketSet*>::iterator i;
	
	for(i=m_socket_sets.begin();i!=m_socket_sets.end();++i)
	{
		(*i)->remove(this);
	}
	
#ifdef WIN32	
	if(--m_winsock_ref_count == 0)
	{
		WSACleanup();
	}
#endif
}

bool Socket::setNonBlock(int socket)
{
#ifdef WIN32		
	unsigned long nonblock=1;
	if(ioctlsocket(socket,FIONBIO,&nonblock)==SOCKET_ERROR)		
#else
	int flags=fcntl(socket,F_GETFL,0);
	if(fcntl(socket,F_SETFL,flags|O_NONBLOCK)==-1)		
#endif
		return false;
	
	return true;
}

bool Socket::isWritePending()
{
	if(m_write_buffer.size()>0)
		return true;
	else
		return false;
}

void Socket::commitWrite()
{
	if(m_write_buffer.size() == 0)
		return;
	
	int res;
		
	do
	{	
		res=send(m_socket,m_write_buffer.c_str(),m_write_buffer.size(),0);
		
		if(res==SOCKET_ERROR)
		{
#ifdef WIN32
			if(WSAGetLastError()!=WSAEWOULDBLOCK)		
#else
			if(errno!=EWOULDBLOCK)	
#endif
			{
				std::cerr<<"Writing to socket failed: "<<getErrorMessage()<<std::endl;	
			}
			
			return;
		}
		
		m_write_buffer.erase(0,res);
	}
	while(res);
}

void Socket::captureSocket(int socket)
{
	close();
	
	m_socket=socket;
}

int Socket::releaseSocket()
{
	int socket=m_socket;
	m_socket=0;
	return socket;
}

std::string Socket::getErrorMessage()
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



