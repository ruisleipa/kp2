#ifndef PACKET_HPP
#define PACKET_HPP

#include <sstream>
#include <string>
#include <stdint.h>

class EndOfDataException
{

};

class Packet
{
	public:
		const Packet& operator<<(uint16_t value);
		const Packet& operator<<(uint32_t value);
		const Packet& operator<<(int16_t value);
		const Packet& operator<<(int32_t value);
		const Packet& operator<<(float value);
		const Packet& operator<<(const std::string& value);
		
		const Packet& operator>>(uint16_t& value);
		const Packet& operator>>(uint32_t& value);
		const Packet& operator>>(int16_t& value);
		const Packet& operator>>(int32_t& value);
		const Packet& operator>>(float& value);
		const Packet& operator>>(std::string& value);
				
		std::string getString() const;
		
		uint16_t getType() const;
		void setType(uint16_t type);		
		
		void readFromBuffer(std::string& buffer);
		
		Packet();
		
		friend std::ostream& operator<<(std::ostream& stream,const Packet& packet);

	private:
		uint16_t m_type;
		std::stringstream m_payload;
};

#endif // PACKET_HPP

