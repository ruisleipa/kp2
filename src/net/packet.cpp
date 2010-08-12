#include "packet.hpp"

#include <iostream>
#include <iomanip>
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
	
	return *this;
}

const Packet& Packet::operator<<(uint32_t value)
{
	uint32_t v=htonl(value);

	m_payload.write((char*)&v,sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(int16_t value)
{
	int16_t v=htons(value);

	m_payload.write((char*)&v,sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(int32_t value)
{
	int32_t v=htonl(value);

	m_payload.write((char*)&v,sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(float value)
{
	int32_t whole;
	uint32_t fract;
	
	whole=int32_t(value);
	fract=(fabs(value)-fabs(whole))*1000000000.0;	
	
	operator<<(whole);
	operator<<(fract);
	
	return *this;
}

const Packet& Packet::operator<<(const std::string& value)
{
	m_payload<<value;
	m_payload.put(0);
	
	return *this;
}

const Packet& Packet::operator>>(uint16_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohs(value);
	
	return *this;
}

const Packet& Packet::operator>>(uint32_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohl(value);
	
	return *this;
}

const Packet& Packet::operator>>(int16_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohs(value);
	
	return *this;
}

const Packet& Packet::operator>>(int32_t& value)
{
	m_payload.read((char*)&value,sizeof(value));
	
	if(m_payload.eof())
		throw EndOfDataException();
	
	value=ntohl(value);
	
	return *this;
}

const Packet& Packet::operator>>(float& value)
{
	int32_t whole;
	uint32_t fract;
	
	operator>>(whole);
	operator>>(fract);
	
	//FIXME: error with negative numbers
	value=float(whole)+float(fract)/1000000000.0;	
	
	return *this;
}

const Packet& Packet::operator>>(std::string& value)
{
	std::getline(m_payload,value,'\0');
		
	if(m_payload.eof())
		throw EndOfDataException();
	
	return *this;
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
	stream << "Type: " << packet.m_type << std::endl;
	stream << "Content: " << std::endl;
	
	int hex_i=0;
	int char_i=0;
	
	const int bytes_per_row=20;
	
	while(hex_i < str.size() && char_i < str.size())
	{
		int i=0;
	
		while(i < bytes_per_row && hex_i < str.size())
		{
			stream << std::setw(2) << std::setfill('0') << std::hex;
			stream << (unsigned int)((unsigned char)(str[hex_i])) << " ";
			
			hex_i++;
			i++;
		}
		
		i=0;
		
		while(i < bytes_per_row && char_i < str.size())
		{
			if(isprint(str[char_i]))
			{
				stream << str[char_i];
			}
			else
			{
				stream << ".";
			}

			char_i++;
			i++;
		}
		
		stream << std::endl;
	}
	
	stream << std::dec;
	
	return stream;
}


