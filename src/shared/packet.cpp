#include "packet.hpp"

#include "socket.hpp"

void Packet::write(uint16_t value)
{
	uint16_t v=htons(value);

	m_buffer.write((char*)&v,sizeof(v));
}

void Packet::write(uint32_t value)
{
	uint32_t v=htonl(value);

	m_buffer.write((char*)&v,sizeof(v));
}

void Packet::write(std::string value)
{
	m_buffer<<value;
	m_buffer.put(0);
}

void Packet::read(uint16_t& value)
{
	m_buffer.read((char*)&value,sizeof(value));
	
	if(m_buffer.eof())
		throw EndOfDataException();
	
	value=ntohs(value);
}

void Packet::read(uint32_t& value)
{
	m_buffer.read((char*)&value,sizeof(value));
	
	if(m_buffer.eof())
		throw EndOfDataException();
	
	value=ntohl(value);
}

void Packet::read(std::string& value)
{
	std::getline(m_buffer,value,'\0');
		
	if(m_buffer.eof())
		throw EndOfDataException();
}

std::string Packet::getString()
{
	return m_buffer.str();
}

Packet::Packet(std::string str)
{
	m_buffer.str(str);
}

Packet::Packet()
{

}


