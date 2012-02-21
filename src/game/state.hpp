#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
#include <memory>

#include "vehicle.hpp"
#include "part.hpp"
#include "player.hpp"
#include "upgrade.hpp"
#include "id.hpp"
#include "stateactionlistener.hpp"
#include "object.hpp"
#include <stdint.h>

namespace Game
{

class State : public Object
{
	public:
		void addPlayer(Player*);
				
		Object& getPlayers();
		Object& getShopVehicles();
		Object& getShopParts();
		Object& getUpgrades();

		State(const Json::Value&);
	
	private:
		Object* players;
		Object* vehicles;
		Object* parts;
		Object* upgrades;

};

};

#endif

