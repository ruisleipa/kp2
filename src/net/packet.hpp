#ifndef NET_PACKET_HPP
#define NET_PACKET_HPP

#include <sstream>
#include <string>
#include <stdint.h>

namespace Net
{

class EndOfDataException
{

};

class Packet
{
	public:
		const Packet& operator<<(uint8_t value);
		const Packet& operator<<(uint16_t value);
		const Packet& operator<<(uint32_t value);
		const Packet& operator<<(int8_t value);
		const Packet& operator<<(int16_t value);
		const Packet& operator<<(int32_t value);
		const Packet& operator<<(float value);
		const Packet& operator<<(const std::string& value);

		const Packet& operator>>(uint8_t& value);
		const Packet& operator>>(uint16_t& value);
		const Packet& operator>>(uint32_t& value);
		const Packet& operator>>(int8_t& value);
		const Packet& operator>>(int16_t& value);
		const Packet& operator>>(int32_t& value);
		const Packet& operator>>(float& value);
		const Packet& operator>>(std::string& value);

		std::string getString() const;

		uint16_t getType() const;
		void setType(uint16_t type);

		void readFromBuffer(std::string& buffer);

		Packet();
		Packet(const Packet&);

		friend std::ostream& operator<<(std::ostream& stream,const Packet& packet);

	private:
		uint16_t type;
		std::stringstream payload;
};

};

#endif

