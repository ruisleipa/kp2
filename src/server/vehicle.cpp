#include "vehicle.hpp"

#include "gamestate.hpp"
#include "vehiclemodel.hpp"

#include <stdexcept>

const VehicleModel& Vehicle::getModel() const
{
	return gameState->getVehicleModel(vehicleModelName);
}

int Vehicle::getPartCount() const
{
	return parts.size();
}

const Part& Vehicle::getPart(int id) const
{
	return getPartFromVector(id);
}

Part Vehicle::uninstallPart(int id)
{
	Part part = getPartFromVector(id);

	parts.erase(parts.begin() + id);
	
	return part;
}

void Vehicle::installPart(const Part& part)
{
	parts.push_back(part);
}

Vehicle::Vehicle(GameState& gameState,const std::string& modelName):
	gameState(&gameState),
	vehicleModelName(modelName)	
{
	this->gameState->getVehicleModel(vehicleModelName);
}

const Part& Vehicle::getPartFromVector(int id) const
{
	if(id < 0 || id >= parts.size())
		throw std::runtime_error("No such part");
		
	return parts[id];
}
