#include "objectfactory.hpp"

#include <stdexcept>

#include "game/chassis.hpp"
#include "game/crankshaft.hpp"
#include "game/cylinderblock.hpp"
#include "game/cylinderhead.hpp"
#include "game/vehicle.hpp"
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

	if(type == "Chassis")
		return new Game::Chassis(value);
	else if(type == "Crankshaft")
		return new Game::Crankshaft(value);
	else if(type == "CylinderBlock")
		return new Game::CylinderBlock(value);
	else if(type == "CylinderHead")
		return new Game::CylinderHead(value);
	else if(type == "Vehicle")
		return new Game::Vehicle(value, *this);
	else if(type == "Player")
		return new Game::Player(value, *this);
	else if(type == "")
		return new Game::Object(value);

	return nullptr;
}

}
