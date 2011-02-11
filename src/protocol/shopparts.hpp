#ifndef SHOPPARTS_HPP
#define SHOPPARTS_HPP

#include <vector>

#include "shoppart.hpp"

class Packet;

class ShopParts
{
	public:
		size_t getPartCount() const;
		ShopPart getPart(size_t index) const;
		void addPart(const ShopPart& part);
		
		friend Packet& operator<<(Packet& packet,const ShopParts& shopParts);
		friend Packet& operator>>(Packet& packet,ShopParts& shopParts);
		
	private:
		std::vector<ShopPart> parts;

};

#endif // SHOPPARTS_HPP

