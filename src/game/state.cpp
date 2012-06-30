#include "state.hpp"

#include "utils/directory.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>

namespace Game
{

Player* State::createPlayer()
{
	Player* player = new Game::Player(objectFactory);

	players.add(player);
	
	return player;
}
	
const Container<Player>& State::getPlayers() const
{
	return players;
}

const Container<Vehicle>& State::getShopVehicles() const
{
	return vehicles;
}

void State::addShopVehicle(Vehicle* vehicle)
{
	vehicles.add(vehicle);
}

const Container<Part>& State::getShopParts() const
{
	return parts;
}

void State::save(Json::Value& value) const
{
	players.save(value["players"]);
	vehicles.save(value["vehicles"]);
	parts.save(value["parts"]);
}

State::State(ObjectFactory& objectFactory):
	objectFactory(objectFactory)
{

}

State::State(const Json::Value& value, ObjectFactory& objectFactory):
	Object(value),
	objectFactory(objectFactory),
	players(value["players"], objectFactory),
	vehicles(value["vehicles"], objectFactory),
	parts(value["parts"], objectFactory)
{
	
}

};
