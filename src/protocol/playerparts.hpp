#ifndef PLAYERPARTS_HPP
#define PLAYERPARTS_HPP

#include <vector>

#include "playerpart.hpp"

class Packet;

class PlayerParts
{
	public:
		size_t getPartCount() const;
		PlayerPart getPart(size_t index) const;
		void addPart(const PlayerPart& part);
		
		friend Packet& operator<<(Packet& packet,const PlayerParts& playerParts);
		friend Packet& operator>>(Packet& packet,PlayerParts& playerParts);
		
	private:
		std::vector<PlayerPart> parts;

};

#endif // PLAYERPARTS_HPP

