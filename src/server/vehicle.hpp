#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>
#include <vector>

#include "part.hpp"
#include "exceptions.hpp"

class Player;
class GameState;
class VehicleModel;

class Vehicle
{
	public:		
		const VehicleModel& getModel() const;
		
		int getPartCount() const;
		const Part& getPart(int id) const;
		
		void uninstallPart(int id);
		void installPart(int playerPartId);
		
		int getWeight() const;
		
		Vehicle(const VehicleModel& vehicleModel, Player& player);
		
	private:
		const Part& getPartFromVector(int id) const;
	
		const VehicleModel* vehicleModel;
		Player* player;
		
		std::vector<Part> parts;
		
};

#endif // VEHICLE_HPP

