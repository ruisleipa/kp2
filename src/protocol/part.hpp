#ifndef PROTOCOL_PART_HPP
#define PROTOCOL_PART_HPP

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{
	class Part
	{
		public:
			uint32_t id;
			std::string name;
			uint32_t price;
			std::string type;
			float weight;

			friend Packet& operator<<(Packet& packet,const Part& Part);
			friend Packet& operator>>(Packet& packet,Part& Part);
	};
};

#endif

