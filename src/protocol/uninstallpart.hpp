#ifndef PROTOCOL_UNINSTALLPART_HPP
#define PROTOCOL_UNINSTALLPART_HPP

#include "idtypes.hpp"

class Packet;

namespace Protocol
{

class UninstallPart
{
	public:
		Protocol::PartId id;

		friend Packet& operator<<(Packet& packet,const UninstallPart& command);
		friend Packet& operator>>(Packet& packet,UninstallPart& command);

};

};

#endif // PROTOCOL_UNINSTALLPART_HPP

