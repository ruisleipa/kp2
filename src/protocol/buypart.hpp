#ifndef PROTOCOL_BUYPART_HPP
#define PROTOCOL_BUYPART_HPP

#include <string>

class Packet;

class BuyPart
{
	public:
		std::string id;

		friend Packet& operator<<(Packet& packet,const BuyPart& buyPart);
		friend Packet& operator>>(Packet& packet,BuyPart& buyPart);

};

#endif // PROTOCOL_BUYPART_HPP

