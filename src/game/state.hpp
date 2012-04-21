#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
#include <memory>

#include "vehicle.hpp"
#include "part.hpp"
#include "player.hpp"
#include "upgrade.hpp"
#include "object.hpp"
#include "container.hpp"
#include "objectfactory.hpp"
#include <stdint.h>

namespace Game
{

class State : public Object
{
	public:
		Player* createPlayer();

		const Container<Player>& getPlayers() const;
		const Container<Vehicle>& getShopVehicles() const;
		const Container<Part>& getShopParts() const;
		const Container<Upgrade>& getUpgrades() const;

		virtual void save(Json::Value&) const;

		State(const Json::Value&, ObjectFactory&);

	private:
		ObjectFactory& objectFactory;

		Container<Player> players;
		Container<Vehicle> vehicles;
		Container<Part> parts;
		Container<Upgrade> upgrades;

};

};

#endif

