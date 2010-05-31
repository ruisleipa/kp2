#include "socketcore.hpp"

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>

#else

#include <errno.h>
#include <string.h>

#endif

#include <iostream>

SocketCore& SocketCore::getInstance()
{
	static SocketCore instance;

	return instance;
}

std::string SocketCore::getErrorMessage()
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

SocketCore::SocketCore()
{
#ifdef WIN32
	WSADATA wsaData;
	
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		LPSTR err=NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0,WSAGetLastError(),0,(LPSTR)&err,0,0);	
		std::cerr<<"WSAStartup failed:"<<err<<std::endl;
		LocalFree(err);
		exit(1);
	}
#endif
}

SocketCore::~SocketCore()
{
#ifdef WIN32
	WSACleanup();
#endif
}
