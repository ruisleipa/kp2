#include "part.hpp"

#include "machining.hpp"
#include "partmodel.hpp"

#include <stdexcept>

const std::string& Part::getName() const
{
	return partModel->getName();
}

int Part::getPrice() const
{
	return partModel->getPrice();
}

const std::string& Part::getType() const
{
	return partModel->getType();
}

float Part::getWeight() const
{
	return partModel->getWeight();
}

bool Part::fitsInVehicle(const Vehicle& vehicle) const
{
	return partModel->fitsInVehicle(vehicle);
}

void Part::addMachining(const Machining& machining)
{
	if(machining.fitsForPart(*this))
		machinings.insert(&machining);
	else
		throw std::runtime_error("Machining \"\" does not fit for part model \"\"");
}

Part::Part(const PartModel& partModel):
	partModel(&partModel)	
{

}
