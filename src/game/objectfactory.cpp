#include "objectfactory.hpp"

#include <stdexcept>
#include <sstream>

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
#include "injector.hpp"
#include "intakemanifold.hpp"
#include "tire.hpp"
#include "transmission.hpp"
#include "vehicle.hpp"
#include "upgrade.hpp"
#include "player.hpp"

namespace Game
{

Object* ObjectFactory::create(const Json::Value& value)
{
	std::string type;
	
	type = value["type"].asString();
	
	Object* object = nullptr;
	
	if(type == "camshaft")
		object = new Camshaft(value);
	else if(type == "charger")
		object = new Charger(value);
	else if(type == "clutch")
		object = new Clutch(value);
	else if(type == "cooler")
		object = new Cooler(value);
	else if(type == "cylinderhead")
		object = new CylinderHead(value);
	else if(type == "differential")
		object = new Differential(value);
	else if(type == "engine")
		object = new Engine(value);
	else if(type == "exhaustmanifold")
		object = new ExhaustManifold(value);
	else if(type == "exhaustpipe")
		object = new ExhaustPipe(value);
	else if(type == "fuelintake")
		object = new FuelIntake(value);
	else if(type == "fuelpump")
		object = new FuelPump(value);
	else if(type == "injector")
		object = new Injector(value);
	else if(type == "intakemanifold")
		object = new IntakeManifold(value);
	else if(type == "tire")
		object = new Tire(value);
	else if(type == "transmission")
		object = new Transmission(value);
	else if(type == "vehicle")
		object = new Vehicle(value);
	else if(type == "player")
		object = new Player(value);
	else if(type == "")
		object = new Object(value);
	
	if(object == nullptr)
		throw std::runtime_error("Invalid object type \"" + type + "\"");
	
	return object;
}

}
