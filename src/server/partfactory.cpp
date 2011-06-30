#include "partfactory.hpp"

#include "utils/inifile.hpp"

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

Part* PartFactory::loadPart(const std::string& filename)
{
	IniFile partFile(filename);
	
	std::string type;
	
	partFile.getValue("type", type);
	
	if(type == "camshaft")
		return new Camshaft(partFile);
	else if(type == "charger")
		return new Charger(partFile);
	else if(type == "clutch")
		return new Clutch(partFile);
	else if(type == "cooler")
		return new Cooler(partFile);
	else if(type == "cylinderhead")
		return new CylinderHead(partFile);
	else if(type == "differential")
		return new Differential(partFile);
	else if(type == "engine")
		return new Engine(partFile);
	else if(type == "exhaustmanifold")
		return new ExhaustManifold(partFile);
	else if(type == "exhaustpipe")
		return new ExhaustPipe(partFile);
	else if(type == "fuelintake")
		return new FuelIntake(partFile);
	else if(type == "fuelpump")
		return new FuelPump(partFile);
	else if(type == "injector")
		return new Injector(partFile);
	else if(type == "intakemanifold")
		return new IntakeManifold(partFile);
	else if(type == "tire")
		return new Tire(partFile);
	else if(type == "transmission")
		return new Transmission(partFile);
	
	throw std::runtime_error("Invalid part type \"" + type + "\" in file \"" + filename + "\".");
}
