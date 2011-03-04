#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>

class VehicleModel;
class PartModel;

#include "part.hpp"
#include "vehicle.hpp"
#include "exceptions.hpp"

class Player
{
	public:		
		const std::string& getName() const;
		void setName(const std::string& name);
		
		int getMoney() const;
		
		void buyVehicle(const VehicleModel& model);
		void buyPart(const PartModel& model);

		std::vector<int> getVehicleIds() const;
		Vehicle& getVehicle(int id);
		
		std::vector<int> getPartIds() const;
		const Part& getPart(int id) const;
		void addPart(const Part& part);
		void removePart(int id);
		
		void setActiveVehicleId(int id);
		int getActiveVehicleId();
		
		Player(const std::string& name,int money);
		
	private:
		std::string name;
		int money;
		
		int activeVehicleId;
	
		std::map<int,Vehicle> vehicles;
		std::map<int,Part> parts;
		
};

#endif // PLAYER_HPP

