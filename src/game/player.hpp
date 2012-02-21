#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include <memory>
#include <set>

#include "part.hpp"
#include "vehicle.hpp"
#include "playeractions.hpp"
#include "playeractionlistener.hpp"
#include "object.hpp"

namespace Game
{

class Player : public PlayerActions, public Object
{
	public:		
		virtual void setName(const std::string& name);
		virtual void setActiveVehicle(Vehicle* vehicle);
		
		virtual void buyPart(const Part* part);
		virtual void buyVehicle(const Vehicle* vehicle);
		
		virtual void attachPart(Part* part);
		virtual void detachPart(Part* part);
		virtual void upgradePart(Part* part, const Upgrade* upgrade);		

		const std::string& getName() const;
		
		int getMoney() const;
		
		Object& getVehicles() const; 
		Object& getParts() const; 
		
		Vehicle* getActiveVehicle() const;
		
		Player(const std::string& name,int money);		
		Player(const Json::Value& value);
		
		virtual void save(Json::Value& value);
		
	private:
		std::string name;
		int money;		
		Vehicle* activeVehicle;
		
		Object* parts;
		Object* vehicles;
		
		std::set<PlayerActionListener*> listeners;
};

};

#endif
