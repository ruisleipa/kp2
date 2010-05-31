#include "clientsocket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int ClientSocket::open(std::string host,int port)
{
	close();

	getAddresses(host.c_str(),port);
	
	addrinfo* p;
	
	while((p=nextAddress()))
	{
		m_socket=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		
		if(!isSocketValid())
			continue;
			
		if(connect(m_socket,p->ai_addr,p->ai_addrlen)==-1)
		{
			close();
			continue;			
		}
		
		break;
	}
	
	freeAddresses();
	
	if(p==0)
		return -1;

	return 0;
}

int ClientSocket::read(char* data,int size)
{
	if(!isSocketValid())
		return 0;

	int read;

	while(size)
	{
		read=recv(m_socket,data,size,0);
		
		if(read==-1)
		{
			//error
		}
		
		if(read==0)
		{
			close();
			return 0;
		}
		
		data+=read;
		size-=read;
	}
	
	return 1;
}

void ClientSocket::write(const char* data,int size)
{
	if(!isSocketValid())
		return;

	int sent;

	while(size)
	{
		sent=send(m_socket,data,size,0);
	
		if(sent==-1)
		{
			//error
		}		
			
		data+=sent;
		size-=sent;
	}	
}

