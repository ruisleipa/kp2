#include "clientsocket.hpp"

bool ClientSocket::connect(const std::string& hostname,int port)
{
	return connectImpl(hostname,port);
}

int ClientSocket::read(char* data,int size)
{
	return readImpl(data,size);
}

int ClientSocket::write(const char* data,int size)
{
	return writeImpl(data,size);	
}

ClientSocket::ClientSocket()
{

}
/*
const int& ClientSocket::getSocket()
{
	return m_socket;
}
*/
