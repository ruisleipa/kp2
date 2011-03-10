#include "partmodel.hpp"

#include "utils/inifile.hpp"

#include "partmodelimplementation.hpp"

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
	return partModelImplementation->getName();
}

int PartModel::getPrice() const
{
	return partModelImplementation->getPrice();
}

const std::string& PartModel::getType() const
{
	return type;
}

float PartModel::getWeight() const
{
	return weight;
}

const PartModelImplementation& PartModel::getImplementation() const
{
	return *partModelImplementation;
}

void PartModel::checkInstallationConstraints(const Vehicle& vehicle) const
{
	partModelImplementation->checkInstallationConstraints(vehicle);
}

void PartModel::checkKeepingConstraints(const Vehicle& vehicle) const
{
	partModelImplementation->checkKeepingConstraints(vehicle);
}

PartModel::PartModel():
	price(0),
	type(""),
	weight(0.0),
	partModelImplementation(0)
{

}
	
PartModel::PartModel(const std::string& filename)
{
	load(filename);
}

PartModel::~PartModel()
{

}

void PartModel::load(const std::string& filename)
{
	IniFile partFile(filename);
	
	partFile.getValue("type",type);
	partFile.getValue("weight",weight);
	price = 100;
	
	PartModelImplementation* impl = 0;
	
	if(type == "camshaft")
		impl = new Camshaft(partFile);
	else if(type == "charger")
		impl = new Charger(partFile);
	else if(type == "clutch")
		impl = new Clutch(partFile);
	else if(type == "cooler")
		impl = new Cooler(partFile);
	else if(type == "cylinderhead")
		impl = new CylinderHead(partFile);
	else if(type == "differential")
		impl = new Differential(partFile);
	else if(type == "engine")
		impl = new Engine(partFile);
	else if(type == "exhaustmanifold")
		impl = new ExhaustManifold(partFile);
	else if(type == "exhaustpipe")
		impl = new ExhaustPipe(partFile);
	else if(type == "fuelintake")
		impl = new FuelIntake(partFile);
	else if(type == "fuelpump")
		impl = new FuelPump(partFile);
	else if(type == "injector")
		impl = new Injector(partFile);
	else if(type == "intakemanifold")
		impl = new IntakeManifold(partFile);
	else if(type == "tire")
		impl = new Tire(partFile);
	
	if(impl == 0)
		throw std::runtime_error("Invalid part type \"" + type + "\" in file \"" + filename + "\".");
		
	partModelImplementation = impl;
}
