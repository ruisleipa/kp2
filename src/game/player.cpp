#include "player.hpp"

#include <algorithm>

namespace Game
{

void Player::setName(const std::string& name)
{
	this->name = name;
	
	for(PlayerActionListener* l : listeners)
		l->setName(name);
	
	changed();
}

void Player::setActiveVehicle(Vehicle* vehicle)
{
	if(vehicles.getIndexOf(vehicle) != -1)
		activeVehicle = vehicle;
}

void Player::buyPart(const Part* part)
{
	if(money >= part->getPrice())
	{
		money -= part->getPrice();
		changed();
		
		parts.add(part->clone());
	}
}

void Player::buyVehicle(const Vehicle* vehicle)
{
	if(money >= vehicle->getPrice())
	{
		money -= vehicle->getPrice();
		changed();
		
		vehicles.add(vehicle->clone());
	}
}

void Player::attachPart(Part* part)
{
	if(!getActiveVehicle())
		return;
		
	auto it = std::find(parts->begin(), parts->end(), part);
	
	if(it == parts->end())
		return;

}

void Player::detachPart(Part* part)
{
	if(!getActiveVehicle())
		return;
	
/*	if(getActiveVehicle()->detachPart(part))
		parts.insert(part);*/
}
		
void Player::upgradePart(Part* part, const Upgrade* upgrade)
{
	(void)part;
	(void)upgrade;
}

const std::string& Player::getName() const
{
	return name;
}

int Player::getMoney() const
{
	return money;
}

Object& Player::getVehicles() const
{
	return *vehicles;
}

Object& Player::getParts() const
{
	return *parts;
}

Vehicle* Player::getActiveVehicle() const
{
	return activeVehicle;
}

Player::Player(const std::string& name, int money):
	name(name),
	money(money),
	activeVehicle(nullptr)
{
	vehicles = new Object();
	vehicles->setName("vehicles");
	
	parts = new Object();
	parts->setName("parts");
	
	addChild(vehicles);
	addChild(parts);
}

Player::Player(const Json::Value& value):
	Object(value)
{
	name = value["name"].asString();
	money = value["money"].asUInt();
	
	Object* activeVehicle = resolveId(value["activeVehicle"]);
	
	vehicles = findChild("vehicles");
	parts = findChild("parts");
}

void Player::save(Json::Value& value)
{
	Object::save(value);

	value["type"] = "player";
	value["name"] = name;
	value["money"] = money;
	value["activeVehicle"] = getId(activeVehicle);
}

};
