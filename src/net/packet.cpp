#include "packet.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

const Packet& Packet::operator<<(uint8_t value)
{
	payload.write((char*)&value, sizeof(value));
	
	return *this;
}

const Packet& Packet::operator<<(uint16_t value)
{
	uint16_t v = htons(value);

	payload.write((char*)&v, sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(uint32_t value)
{
	uint32_t v = htonl(value);

	payload.write((char*)&v, sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(int8_t value)
{
	payload.write((char*)&value, sizeof(value));
	
	return *this;
}

const Packet& Packet::operator<<(int16_t value)
{
	int16_t v = htons(value);

	payload.write((char*)&v, sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(int32_t value)
{
	int32_t v = htonl(value);

	payload.write((char*)&v, sizeof(v));
	
	return *this;
}

const Packet& Packet::operator<<(float value)
{
	int32_t whole;
	uint32_t fract;
	
	whole = int32_t(value);
	fract = (fabs(value) - fabs(whole)) * 1000000000.0;
	
	operator<<(whole);
	operator<<(fract);
	
	return *this;
}

const Packet& Packet::operator<<(const std::string& value)
{
	if(value.size() > std::numeric_limits<uint16_t>::max())
		std::runtime_error("Too long string for sending");

	operator<<(uint16_t(value.size()));
	payload.write(value.c_str(), value.size());
	
	return *this;
}

const Packet& Packet::operator>>(uint8_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	return *this;
}

const Packet& Packet::operator>>(uint16_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	value = ntohs(value);
	
	return *this;
}

const Packet& Packet::operator>>(uint32_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	value = ntohl(value);
	
	return *this;
}

const Packet& Packet::operator>>(int8_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	return *this;
}

const Packet& Packet::operator>>(int16_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	value = ntohs(value);
	
	return *this;
}

const Packet& Packet::operator>>(int32_t& value)
{
	payload.read((char*)&value, sizeof(value));
	
	if(payload.eof())
		throw EndOfDataException();
	
	value = ntohl(value);
	
	return *this;
}

const Packet& Packet::operator>>(float& value)
{
	int32_t whole;
	uint32_t fract;
	
	operator>>(whole);
	operator>>(fract);
	
	value = float(fabs(whole)) + float(fract) / 1000000000.0;
	
	if(whole < 0)
		value *= -1.0;
	
	return *this;
}

const Packet& Packet::operator>>(std::string& value)
{
	value = "";

	uint16_t size;
	
	operator>>(size);
	
	while(size > 0)
	{
		char c;
		
		payload.read(&c, 1);
		
		if(payload.eof())
			throw EndOfDataException();
	
		value.push_back(c);
	
		size--;
	}
	
	return *this;
}

std::string Packet::getString() const
{
	std::string str;
	std::string payload = this->payload.str();
	
	uint16_t size = htons(payload.size() + 4);
	uint16_t type = htons(this->type);
	
	str.append((char*)&size, sizeof(size));
	str.append((char*)&type, sizeof(type));
	str.append(payload);
	
	return str;
}

uint16_t Packet::getType() const
{
	return type;
}

void Packet::setType(uint16_t type)
{
	this->type = type;
}

void Packet::readFromBuffer(std::string& buffer)
{
	if(buffer.size() < 4)
		throw EndOfDataException();
	
	uint16_t length;
	uint16_t type;
		
	buffer.copy((char*)&length, sizeof(length));
	buffer.copy((char*)&type, sizeof(type),2);	
	
	length=ntohs(length);
	type=ntohs(type);
	
	if(buffer.size() < length)
		throw EndOfDataException();
		
	this->type = type;
	this->payload.str(std::string(buffer, 4, length-4));	
	buffer.erase(0, length);	
}

Packet::Packet():
	type(0),
	payload("")
{

}

Packet::Packet(const Packet& packet)
{
	type = packet.type;
	payload.str(packet.payload.str());
	payload.seekp(packet.payload.str().size());
}

std::ostream& operator<<(std::ostream& stream,const Packet& packet)
{
	std::string str=packet.payload.str();

	stream << "---Packet---" << std::endl;
	stream << "Type: " << packet.type << std::endl;
	stream << "Payload size: " << str.size() << std::endl;
	stream << "Payload: " << std::endl;
	
	size_t hex_i=0;
	size_t char_i=0;
	
	const int bytes_per_row=20;
	
	while(hex_i < str.size() && char_i < str.size())
	{
		int i=0;
	
		while(i < bytes_per_row)
		{
			stream << std::setw(2) << std::setfill('0') << std::hex;
			
			if(hex_i < str.size())
				stream << (unsigned int)((unsigned char)(str[hex_i])) << " ";
			else
				stream << "  " << " ";
			
			hex_i++;
			i++;
		}
		
		i=0;
		
		while(i < bytes_per_row)
		{
			if(char_i < str.size())
			{
				if(isprint(str[char_i]))
					stream << str[char_i];
				else
					stream << ".";
			}
			else
			{
				stream << " ";
			}
			
			char_i++;
			i++;
		}
		
		stream << std::endl;
	}
	
	stream << std::dec;
	
	return stream;
}


