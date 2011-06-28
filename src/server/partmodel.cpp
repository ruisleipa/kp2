#include "partmodel.hpp"

#include "utils/inifile.hpp"

#include "partmodel.hpp"

//#include "accessory.hpp"
#include "camshaft.hpp"
#include "charger.hpp"
#include "clutch.hpp"
#include "cooler.hpp"
#include "cylinderhead.hpp"
#include "differential.hpp"
#include "engine.hpp"
#include "exhaustmanifold.hpp"
#include "exhaustpipe.hpp"
#include "fuelintake.hpp"
#include "fuelpump.hpp"
#include "gamestate.hpp"
#include "injector.hpp"
#include "intakemanifold.hpp"
#include "tire.hpp"
#include "transmission.hpp"

const std::string& PartModel::getName() const
{
	return name;
}

int PartModel::getPrice() const
{
	return price;
}

const std::string& PartModel::getType() const
{
	return type;
}

float PartModel::getWeight() const
{
	return weight;
}

void PartModel::checkInstallationConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
	checkForExtraPartsOfThisType(vehicle);
}

void PartModel::checkKeepingConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
}

void PartModel::checkPrerequisiteParts(const Vehicle& vehicle) const
{

}

void PartModel::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{

}

PartModel::PartModel(const IniFile& partFile)
{
	partFile.getValue("type",type);
	partFile.getValue("weight",weight);
	name = partFile.getValueWithDefault("name", "Nimetön osa");
	price = partFile.getValueWithDefault("price", 0);
}
