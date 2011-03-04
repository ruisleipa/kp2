#include "vehicle.hpp"

#include "player.hpp"
#include "gamestate.hpp"
#include "vehiclemodel.hpp"

#include <stdexcept>

const VehicleModel& Vehicle::getModel() const
{
	return *vehicleModel;
}

int Vehicle::getPartCount() const
{
	return parts.size();
}

const Part& Vehicle::getPart(int id) const
{
	return getPartFromVector(id);
}

void Vehicle::uninstallPart(int id)
{
	player->addPart(getPart(id));
	parts.erase(parts.begin() + id);	
}

void Vehicle::installPart(int playerPartId)
{
	const Part& newPart = player->getPart(playerPartId);
	
	if(!newPart.fitsInVehicle(*this))
		return;

	parts.push_back(newPart);
	
	player->removePart(playerPartId);	
}

int Vehicle::getWeight() const
{
	int weight = getModel().getChassisWeight();

	for(int i = 0; i < getPartCount(); ++i)
	{
		weight += getPart(i).getWeight();
	}
	
	return weight;
}

Vehicle::Vehicle(const VehicleModel& vehicleModel, Player& player):
	vehicleModel(&vehicleModel),
	player(&player)	
{
	for(int i = 0; i < getModel().getPartCount(); ++i)
	{
		parts.push_back(getModel().getPart(i));
	}
}

const Part& Vehicle::getPartFromVector(int id) const
{
	if(id < 0 || id >= parts.size())
		throw NoSuchPartException();
		
	return parts[id];
}
