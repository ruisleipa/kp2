#include "socketset.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <iostream>

#include "string.hpp"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

void SocketSet::add(Socket* socket)
{
	if(socket->m_socket>m_highest_fd)
		m_highest_fd=socket->m_socket;
		
	socket->m_socket_sets.push_back(this);
		
	FD_SET(socket->m_socket,&m_fd_set);
	
	m_sockets[socket->m_socket]=socket;
}

void SocketSet::remove(Socket* socket)
{
	std::map<int,Socket*>::iterator s;
	
	for(s=m_sockets.begin();s!=m_sockets.end();s++)
	{
		if((*s).second==socket)
			break;
	}	
	
	if(s==m_sockets.end())
		return;
	
	FD_CLR((*s).first,m_fd_set);
	
	if((*s).first<m_highest_fd)
	{
		int i=m_highest_fd-1;
		m_highest_fd=0;
			
		for(;i>=0;i--)
		{
			if(FD_ISSET(i,&m_fd_set))
			{
				m_highest_fd=i;
				break;
			}
		}
	}
	
	m_sockets.erase(s);
}

Socket* SocketSet::waitForActivity()
{
	/*
	We call select if this is the first wait or the sockets of the last
	select	have been processed. In the latter case m_current_active is
	larger than m_highest_fd because the loop that checks the sockets stops 
	only after the m_current_active is higher than m_highest_fd.
	*/
	if(m_first_wait || m_current_active>m_highest_fd)
	{
		m_first_wait=false;
	
		m_active_sockets=m_fd_set;
		
		if(select(m_highest_fd+1,&m_active_sockets,0,0,0)==-1)
		{
			perror("select");
		}
		
		m_current_active=0;
	}	
	
	for(;m_current_active<=m_highest_fd;m_current_active++)
	{
		if(FD_ISSET(m_current_active,&m_active_sockets))
		{
			return m_sockets[m_current_active++];
		}
	}
	
	/*
	We have gone through all the sockets so we call this function again as
	it will check this condition and act appropriately. This is done in
	this way because I didn't want to copy the socket cheking loop. If you
	come up with a better solution, please let me know.
	*/
	return waitForActivity();
}

SocketSet::SocketSet()
{
	m_highest_fd=0;
	FD_ZERO(&m_fd_set);
	m_current_active=0;
	m_first_wait=true;
}

SocketSet::~SocketSet()
{

}

