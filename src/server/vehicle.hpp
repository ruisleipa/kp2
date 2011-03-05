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
		
		size_t getPartCount() const;
		const Part& getPart(size_t id) const;
		
		void uninstallPart(size_t id);
		void installPart(size_t playerPartId);
		
		int getWeight() const;
		
		Vehicle(const VehicleModel& vehicleModel, Player& player);
		
	private:
		void addPart(const Part& part);
		void removePart(size_t id);
	
		const Part& getPartFromVector(size_t id) const;
	
		const VehicleModel* vehicleModel;
		Player* player;
		
		std::vector<Part> parts;
		
};

#endif // VEHICLE_HPP

