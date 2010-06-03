#ifndef __COMMAND_HPP
#define __COMMAND_HPP

#include <sstream>

#include "shared/packet.hpp"

class Command
{
	public:
		virtual void process(Packet& packet,Packet& response)=0;		
};

#endif // __COMMAND_HPP

