#include "playervehicles.hpp"

#include "net/packet.hpp"

#include <iostream>

size_t PlayerVehicles::getVehicleCount() const
{
	return vehicles.size();
}

PlayerVehicle PlayerVehicles::getVehicle(size_t index) const
{
	return vehicles.at(index);
}

void PlayerVehicles::addVehicle(const PlayerVehicle& vehicle)
{
	vehicles.push_back(vehicle);
}

Packet& operator<<(Packet& packet,const PlayerVehicles& playerVehicles)
{
	packet << uint32_t(playerVehicles.vehicles.size());
	
	for(size_t i = 0; i < playerVehicles.vehicles.size(); ++i)
	{
		packet << playerVehicles.vehicles[i];
	}
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerVehicles& playerVehicles)
{
	playerVehicles.vehicles.clear();

	uint32_t vehicleCount;
	
	packet >> vehicleCount;
	
	for(size_t i = 0; i < vehicleCount; ++i)
	{
		PlayerVehicle playerVehicle;
		
		packet >> playerVehicle;
		
		std::cout << playerVehicle.name << std::endl;
		
		playerVehicles.vehicles.push_back(playerVehicle);
	}
		
	return packet;
}