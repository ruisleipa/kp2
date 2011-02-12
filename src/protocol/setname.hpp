#ifndef SETNAME_HPP
#define SETNAME_HPP

#include <string>

class Packet;

namespace Protocol
{

class SetName
{
	public:
		std::string name;

		friend Packet& operator<<(Packet& packet,const SetName& setName);
		friend Packet& operator>>(Packet& packet,SetName& setName);

};

};

#endif // SETNAME_HPP

