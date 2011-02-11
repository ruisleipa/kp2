#include "playerparts.hpp"

#include "net/packet.hpp"

#include <iostream>

size_t PlayerParts::getPartCount() const
{
	return parts.size();
}

PlayerPart PlayerParts::getPart(size_t index) const
{
	return parts.at(index);
}

void PlayerParts::addPart(const PlayerPart& playerPart)
{
	parts.push_back(playerPart);
}

Packet& operator<<(Packet& packet,const PlayerParts& playerParts)
{
	packet << uint32_t(playerParts.parts.size());
	
	for(size_t i = 0; i < playerParts.parts.size(); ++i)
	{
		packet << playerParts.parts[i];
	}
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerParts& playerParts)
{
	playerParts.parts.clear();

	uint32_t partCount;
	
	packet >> partCount;
	
	for(size_t i = 0; i < partCount; ++i)
	{
		PlayerPart playerPart;
		
		packet >> playerPart;
		
		playerParts.parts.push_back(playerPart);
	}
		
	return packet;
}