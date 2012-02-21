#include "state.hpp"

#include "utils/directory.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>

namespace Game
{

void State::addPlayer(Player* player)
{
	addChild(player);
}
	
Object& State::getPlayers()
{
	return *players;
}

Object& State::getShopVehicles()
{
	return *vehicles;
}

Object& State::getShopParts()
{
	return *parts;
}

Object& State::getUpgrades()
{
	return *upgrades;
}

State::State(const Json::Value& value):
	Object(value)
{
	players = findChild("players");
	vehicles = findChild("vehicles");
	parts = findChild("parts");
	upgrades = findChild("upgrades");
}

};
