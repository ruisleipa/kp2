#include "state.hpp"

#include <stdexcept>

namespace Client
{

Game::Player* State::getPlayer()
{
	return player;
}

State::State(const Json::Value& value):
	Game::State(value)
{
	Object* obj = resolveId(value["client"]["playerId"]);

	if(!obj)
		throw std::runtime_error("Client::State::State: Cannot resolve player ID");

	player = dynamic_cast<Game::Player*>(obj);

	if(!player)
		throw std::runtime_error("Client::State::State: Referenced object is not a Player");
}

void State::save(Json::Value& value)
{	
	Game::State::save(value);

	value["client"]["playerId"] = getId(player);
}

};
