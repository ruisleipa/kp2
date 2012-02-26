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
	player = getPlayers().getByIndex(value["client"]["playerId"].asInt());
}

void State::save(Json::Value& value)
{	
	Game::State::save(value);

	value["client"]["playerId"] = getPlayers().getIndexOf(player);
}

};
