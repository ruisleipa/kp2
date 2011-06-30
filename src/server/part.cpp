#include "part.hpp"

#include "machining.hpp"

#include <stdexcept>

const std::string& Part::getName() const
{
	return name;
}

int Part::getPrice() const
{
	return price;
}

const std::string& Part::getType() const
{
	return type;
}

float Part::getWeight() const
{
	return weight;
}

void Part::checkInstallationConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
	checkForExtraPartsOfThisType(vehicle);
}

void Part::checkKeepingConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
}

void Part::checkPrerequisiteParts(const Vehicle& vehicle) const
{

}

void Part::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{

}

void Part::addMachining(const Machining& machining)
{
	if(machining.fitsForPart(*this))
		machinings.insert(&machining);
	else
		throw std::runtime_error("Machining \"\" does not fit for part model \"\"");
}

Part::Part(const IniFile& partFile)
{
	partFile.getValue("type",type);
	partFile.getValue("weight",weight);
	name = partFile.getValueWithDefault("name", "Nimetön osa");
	price = partFile.getValueWithDefault("price", 0);
}

Part::Part(const Part& b):
	type(b.type),
	name(b.name),
	price(b.price),
	weight(b.weight)
{

}

Part& Part::operator=(const Part& b)
{
	type = b.type;
	name = b.name;
	price = b.price;
	weight = b.weight;
}
