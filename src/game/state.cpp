#include "state.hpp"

#include "utils/directory.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>

namespace Game
{

void State::addPlayer(Player* player)
{
	players.add(player);
}
	
const Container<Player>& State::getPlayers()
{
	return *players;
}

const Container<Player>& State::getShopVehicles()
{
	return *vehicles;
}

const Container<Player>& State::getShopParts()
{
	return *parts;
}

const Container<Player>& State::getUpgrades()
{
	return *upgrades;
}

void State::save(Json::Value&) const
{
	players.save(value["players"]);
	vehicles.save(value["vehicles"]);
	parts.save(value["parts"]);
	upgrades.save(value["upgrades"]);
}

State::State(const Json::Value& value):
	Object(value),
	players(value["players"]),
	vehicles(value["vehicles"]),
	parts(value["parts"]),
	upgrades(value["upgrades"])
{
	
}

};
