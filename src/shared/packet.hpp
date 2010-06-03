#ifndef __PACKET_HPP
#define __PACKET_HPP

#include <sstream>
#include <string>
#include <stdint.h>

class EndOfDataException
{

};

class Packet
{
	public:
		void write(uint16_t value);
		void write(uint32_t value);
		void write(std::string value);
		
		void read(uint16_t& value);
		void read(uint32_t& value);
		void read(std::string& value);
		
		std::string getString();
		
		Packet(std::string str);
		Packet();

	private:
		std::stringstream m_buffer;
};

#endif // __PACKET_HPP

