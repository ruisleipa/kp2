#include "packet.hpp"

#include <iostream>
#include <cmath>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

const Packet& Packet::operator<<(uint16_t value)
{
	uint16_t v=htons(value);

	m_payload.write((char*)&v,sizeof(v));
}

const Packet& Packet::operator<<(uint32_t value)
{
	uint32_t v=htonl(value);

	m_payload.write((char*)&v,sizeof(v));
}

const Packet& Packet::operator<<(int16_t value)
{
	int16_t v=htons(value);

	m_payload.write((char*)&v,sizeof(v));
}

const Packet& Packet::operator<<(int32_t value)
{
	int32_t v=htonl(value);

	m_payload.write((char*)&v,sizeof(v));
}

const Packet& Packet::operator<<(float value)
{
	int32_t whole;
	uint32_t fract;
	
	whole=int32_t(value);
	fract=(fabs(value)-fabs(whole))*1000000000.0;	
	
	operator<<(whole);
	operator<<(fract);
}

const Packet& Packet::operator<<(const std::string& value)
{
	m_payload<<value;
	m_payload.put(0);
}

const Packet& Packet::operator>>(uint16_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohs(value);
}

const Packet& Packet::operator>>(uint32_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohl(value);
}

const Packet& Packet::operator>>(int16_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohs(value);
}

const Packet& Packet::operator>>(int32_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohl(value);
}

const Packet& Packet::operator>>(float& value)
{
	int32_t whole;
	uint32_t fract;
	
	operator>>(whole);
	operator>>(fract);
	
	//FIXME: error with negative numbers
	value=float(whole)+float(fract)/1000000000.0;	
}

const Packet& Packet::operator>>(std::string& value)
{
	std::getline(m_payload,value,'\0');
		
	if(m_payload.eof())
		throw EndOfDataException();
}

std::string Packet::getString() const
{
	std::string str;
	std::string payload=m_payload.str();
	
	uint16_t size=htons(payload.size()+4);
	uint16_t type=htons(m_type);
	
	str.append((char*)&size,sizeof(size));
	str.append((char*)&type,sizeof(type));
	str.append(payload);
	
	if(str.size()>500)
		std::cerr<<"FIXME: Packet size over 500, this may cause buffer overflows. Bad thing."<<std::endl;

	return str;
}

uint16_t Packet::getType() const
{
	return m_type;
}

void Packet::setType(uint16_t type)
{
	m_type=type;
}

void Packet::readFromBuffer(std::string& buffer)
{
	if(buffer.size() < 4)
		throw EndOfDataException();
	
	uint16_t length;
	uint16_t type;
		
	buffer.copy((char*)&length,sizeof(length));
	buffer.copy((char*)&type,sizeof(type),2);	
	
	length=ntohs(length);
	type=ntohs(type);
	
	if(buffer.size() < length)
		throw EndOfDataException();
		
	m_type=type;
	m_payload.str(std::string(buffer,4,length-4));	
	buffer.erase(0,length);	
}

Packet::Packet():
	m_type(0),
	m_payload("")
{

}

std::ostream& operator<<(std::ostream& stream,const Packet& packet)
{
	std::string str=packet.m_payload.str();

	stream << "---Packet---" << std::endl;
	stream << "Size: " << str.size() << std::endl;
	stream << "Type: " << std::hex << packet.m_type  << std::endl;
	stream << "Content: " << std::endl;
	
	for(int i=0;i<str.size();i++)
	{
		stream << str[i] << " ";
		
		/*
		Make a newline after every 30 bytes.
		*/
		if(i != 0 && i%30==0)
			stream << std::endl;
	}
	
	stream << std::dec;
	
	return stream;
}


