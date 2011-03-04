#ifndef PROTOCOL_INSTALLPART_HPP
#define PROTOCOL_INSTALLPART_HPP

#include "idtypes.hpp"

class Packet;

namespace Protocol
{

class InstallPart
{
	public:
		Protocol::PartId id;

		friend Packet& operator<<(Packet& packet,const InstallPart& command);
		friend Packet& operator>>(Packet& packet,InstallPart& command);

};

};

#endif // PROTOCOL_INSTALLPART_HPP

