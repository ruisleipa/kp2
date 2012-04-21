#include "player.hpp"

#include <algorithm>

namespace Game
{

void Player::setName(const std::string& name)
{
	this->name = name;

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
		
		parts.add(Object::clone(part));
	}
}

void Player::buyVehicle(const Vehicle* vehicle)
{
	if(money >= vehicle->getPrice())
	{
		money -= vehicle->getPrice();
		changed();
		
		vehicles.add(Object::clone(vehicle));
	}
}

void Player::attachPart(Part* part)
{
	if(!getActiveVehicle())
		return;
		
	auto it = std::find(parts.begin(), parts.end(), part);
	
	if(it == parts.end())
		return;

}

void Player::detachPart(Part* part)
{
	(void)part;

	if(!getActiveVehicle())
		return;
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

const Container<Vehicle>& Player::getVehicles() const
{
	return vehicles;
}

const Container<Part>& Player::getParts() const
{
	return parts;
}

Vehicle* Player::getActiveVehicle() const
{
	return activeVehicle;
}

Player::Player(ObjectFactory& factory):
	money(0),
	factory(factory)
{

}

Player::Player(const Json::Value& value, ObjectFactory& factory):
	Object(value),
	parts(value["parts"], factory),
	vehicles(value["vehicles"], factory),
	factory(factory)
{
	name = value["name"].asString();
	money = value["money"].asUInt();
	
	activeVehicle = vehicles.getByIndex(value["activeVehicle"].asInt());
}

void Player::save(Json::Value& value)
{
	Object::save(value);

	value["type"] = "player";
	value["name"] = name;
	value["money"] = money;
	value["activeVehicle"] = vehicles.getIndexOf(activeVehicle);
	
	vehicles.save(value["vehicles"]);
	parts.save(value["parts"]);
}

};
