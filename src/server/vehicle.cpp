#include "vehicle.hpp"

#include "player.hpp"
#include "gamestate.hpp"
#include "vehiclemodel.hpp"

#include <stdexcept>

const VehicleModel& Vehicle::getModel() const
{
	return *vehicleModel;
}

size_t Vehicle::getPartCount() const
{
	return parts.size();
}

const Part& Vehicle::getPart(size_t id) const
{
	return getPartFromVector(id);
}

void Vehicle::uninstallPart(size_t id)
{
	player->addPart(getPart(id));
	
	removePart(id);
}

void Vehicle::installPart(size_t playerPartId)
{
	const Part& newPart = player->getPart(playerPartId);
	
	addPart(newPart);	
	
	player->removePart(playerPartId);	
}

int Vehicle::getWeight() const
{
	int weight = getModel().getChassisWeight();

	for(size_t i = 0; i < getPartCount(); ++i)
	{
		weight += getPart(i).getWeight();
	}
	
	return weight;
}

Vehicle::Vehicle(const VehicleModel& vehicleModel, Player& player):
	vehicleModel(&vehicleModel),
	player(&player)	
{
	for(size_t i = 0; i < vehicleModel.getPartCount(); ++i)
	{		
		addPart(vehicleModel.getPart(i));
	}
}

const Part& Vehicle::getPartFromVector(size_t id) const
{
	if(id >= parts.size())
		throw NoSuchPartException();
		
	return parts[id];
}

void Vehicle::addPart(const Part& part)
{
	if(!part.fitsInVehicle(*this))
		throw PartDoesNotFitException();

	parts.push_back(part);
}

void Vehicle::removePart(size_t id)
{
	parts.erase(parts.begin() + id);	
}
