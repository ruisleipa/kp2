#include "socketactivity.hpp"

Socket* SocketActivity::getSocket()
{
	return m_socket;
}

bool SocketActivity::canWrite()
{
	return m_can_write;
}

bool SocketActivity::canRead()
{
	return m_can_read;
}

SocketActivity::SocketActivity()
{
	m_socket=0;
	m_can_read=0;
	m_can_write=0;
}

SocketActivity::SocketActivity(Socket* socket,bool can_read,bool can_write)
{
	m_socket=socket;
	m_can_read=can_read;
	m_can_write=can_write;
}


