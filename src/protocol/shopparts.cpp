#include "shopparts.hpp"

#include "net/packet.hpp"

size_t ShopParts::getPartCount() const
{
	return parts.size();
}

ShopPart ShopParts::getPart(size_t index) const
{
	return parts.at(index);
}

void ShopParts::addPart(const ShopPart& shopPart)
{
	parts.push_back(shopPart);
}

Packet& operator<<(Packet& packet,const ShopParts& shopParts)
{
	packet << uint32_t(shopParts.parts.size());
	
	for(size_t i = 0; i < shopParts.parts.size(); ++i)
	{
		packet << shopParts.parts[i];
	}
	
	return packet;
}

Packet& operator>>(Packet& packet,ShopParts& shopParts)
{
	shopParts.parts.clear();

	uint32_t partCount;
	
	packet >> partCount;
	
	for(size_t i = 0; i < partCount; ++i)
	{
		ShopPart shopPart;
		
		packet >> shopPart;
		
		shopParts.parts.push_back(shopPart);
	}
		
	return packet;
}