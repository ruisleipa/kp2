#ifndef SHOPVEHICLES_HPP
#define SHOPVEHICLES_HPP

#include <vector>

#include "protocol/shopvehicle.hpp"

class Packet;

class ShopVehicles
{
	public:
		size_t getVehicleCount() const;
		ShopVehicle getVehicle(size_t index) const;
		void addVehicle(const ShopVehicle& shopVehicle);
		
		friend Packet& operator<<(Packet& packet,const ShopVehicles& shopVehicles);
		friend Packet& operator>>(Packet& packet,ShopVehicles& shopVehicles);
		
	private:
		std::vector<ShopVehicle> vehicles;

};

#endif // SHOPVEHICLES_HPP

