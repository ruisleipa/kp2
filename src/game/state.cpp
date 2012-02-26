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
	
const Container<Player>& State::getPlayers() const
{
	return players;
}

const Container<Vehicle>& State::getShopVehicles() const
{
	return vehicles;
}

const Container<Part>& State::getShopParts() const
{
	return parts;
}

const Container<Upgrade>& State::getUpgrades() const
{
	return upgrades;
}

void State::save(Json::Value& value) const
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
