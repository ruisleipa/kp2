#ifndef CLIENT_STATE_HPP
#define CLIENT_STATE_HPP

#include "game/state.hpp"

namespace Client
{

class State : public Game::State
{
	public:
		Game::Player* getPlayer();
	
		State(const Json::Value& value, Game::ObjectFactory&);
		
		void save(Json::Value& value) const;
		
	private:
		Game::Player* player;
};

};

#endif

