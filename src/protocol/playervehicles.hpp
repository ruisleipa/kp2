#ifndef PLAYERVEHICLES_HPP
#define PLAYERVEHICLES_HPP

#include <vector>

#include "protocol/playervehicle.hpp"

class Packet;

class PlayerVehicles
{
	public:
		size_t getVehicleCount() const;
		PlayerVehicle getVehicle(size_t index) const;
		void addVehicle(const PlayerVehicle& vehicle);
		
		friend Packet& operator<<(Packet& packet,const PlayerVehicles& playerVehicles);
		friend Packet& operator>>(Packet& packet,PlayerVehicles& playerVehicles);
		
	private:
		std::vector<PlayerVehicle> vehicles;

};

#endif // PLAYERVEHICLES_HPP

