#ifndef __MESSAGEHANDLER_HPP
#define __MESSAGEHANDLER_HPP

#include <sstream>
#include "shared/packet.hpp"

class MessageHandler
{
	public:
		virtual void process(Packet& packet)=0;		
};

#endif // __MESSAGEHANDLER_HPP

