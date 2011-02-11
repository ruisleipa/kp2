#include "shopvehicles.hpp"

#include "net/packet.hpp"

size_t ShopVehicles::getVehicleCount() const
{
	return vehicles.size();
}

ShopVehicle ShopVehicles::getVehicle(size_t index) const
{
	return vehicles.at(index);
}

void ShopVehicles::addVehicle(const ShopVehicle& shopVehicle)
{
	vehicles.push_back(shopVehicle);
}

Packet& operator<<(Packet& packet,const ShopVehicles& shopVehicles)
{
	packet << uint32_t(shopVehicles.vehicles.size());
	
	for(size_t i = 0; i < shopVehicles.vehicles.size(); ++i)
	{
		packet << shopVehicles.vehicles[i];
	}
	
	return packet;
}

Packet& operator>>(Packet& packet,ShopVehicles& shopVehicles)
{
	shopVehicles.vehicles.clear();

	uint32_t vehicleCount;
	
	packet >> vehicleCount;
	
	for(size_t i = 0; i < vehicleCount; ++i)
	{
		ShopVehicle shopVehicle;
		
		packet >> shopVehicle;
		
		shopVehicles.vehicles.push_back(shopVehicle);
	}
		
	return packet;
}