#include "objectfactory.hpp"

#include <stdexcept>

//#include "game/accessory.hpp"
#include "game/camshaft.hpp"
#include "game/charger.hpp"
#include "game/chassis.hpp"
#include "game/clutch.hpp"
#include "game/cooler.hpp"
#include "game/cylinderhead.hpp"
#include "game/differential.hpp"
#include "game/engine.hpp"
#include "game/exhaustmanifold.hpp"
#include "game/exhaustpipe.hpp"
#include "game/fuelintake.hpp"
#include "game/fuelpump.hpp"
#include "game/injector.hpp"
#include "game/intakemanifold.hpp"
#include "game/tire.hpp"
#include "game/transmission.hpp"
#include "game/vehicle.hpp"
#include "game/upgrade.hpp"
#include "game/player.hpp"

namespace Game
{

Object* ObjectFactory::create(const Json::Value& value)
{
	std::string type;

	type = value["type"].asString();

	Object* object = allocate(value);

	if(object == nullptr)
		throw std::runtime_error("Invalid object type \"" + type + "\"");

	return object;
}

Game::Object* ObjectFactory::allocate(const Json::Value& value)
{
	std::string type = value["type"].asString();

	if(type == "camshaft")
		return new Game::Camshaft(value);
	else if(type == "charger")
		return new Game::Charger(value);
	else if(type == "chassis")
		return new Game::Chassis(value);
	else if(type == "clutch")
		return new Game::Clutch(value);
	else if(type == "cooler")
		return new Game::Cooler(value);
	else if(type == "cylinderhead")
		return new Game::CylinderHead(value);
	else if(type == "differential")
		return new Game::Differential(value);
	else if(type == "engine")
		return new Game::Engine(value);
	else if(type == "exhaustmanifold")
		return new Game::ExhaustManifold(value);
	else if(type == "exhaustpipe")
		return new Game::ExhaustPipe(value);
	else if(type == "fuelintake")
		return new Game::FuelIntake(value);
	else if(type == "fuelpump")
		return new Game::FuelPump(value);
	else if(type == "injector")
		return new Game::Injector(value);
	else if(type == "intakemanifold")
		return new Game::IntakeManifold(value);
	else if(type == "tire")
		return new Game::Tire(value);
	else if(type == "transmission")
		return new Game::Transmission(value);
	else if(type == "vehicle")
		return new Game::Vehicle(value, *this);
	else if(type == "player")
		return new Game::Player(value, *this);
	else if(type == "")
		return new Game::Object(value);

	return nullptr;
}

}
