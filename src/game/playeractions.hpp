#ifndef GAME_ACTIONS_HPP
#define GAME_ACTIONS_HPP

#include <string>

#include "vehicle.hpp"
#include "part.hpp"
#include "upgrade.hpp"

namespace Game
{

class PlayerActions
{
	public:
		virtual void setName(const std::string& name) = 0;
		virtual void setActiveVehicle(Vehicle* vehicle) = 0;
		
		virtual void buyPart(const Part* part) = 0;
		virtual void buyVehicle(const Vehicle* vehicle) = 0;
		
		virtual void attachPart(Part* part) = 0;
		virtual void detachPart(Part* part) = 0;		
		virtual void upgradePart(Part* part, const Upgrade* upgrade) = 0;
};

};

#endif

