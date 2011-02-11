#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>

#include "part.hpp"

class GameState;
class VehicleModel;

class Vehicle
{
	public:		
		const VehicleModel& getModel() const;
		
		int getPartCount() const;
		const Part& getPart(int id) const;
		
		Part uninstallPart(int id);
		void installPart(const Part& part);		
		
		Vehicle(GameState& gameState,const std::string& modelName);
		
	private:
		const Part& getPartFromVector(int id) const;
	
		GameState* gameState;
		std::string vehicleModelName;
		
		std::vector<Part> parts;
		
};

#endif // VEHICLE_HPP

