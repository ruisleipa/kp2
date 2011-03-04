#include "player.hpp"

#include "gamestate.hpp"

const std::string& Player::getName() const
{
	return name;
}

void Player::setName(const std::string& name)
{
	this->name = name;
}

int Player::getMoney() const
{
	return money;
}

void Player::buyVehicle(const VehicleModel& vehicleModel)
{
	if(money < vehicleModel.getPrice())
		throw InsufficientMoneyException();
		
	money -= vehicleModel.getPrice();
	
	Vehicle vehicle(vehicleModel, *this);
	
	int newId = 1;
	
	if(vehicles.rbegin() != vehicles.rend())
		newId = vehicles.rbegin()->first + 1;
	
	vehicles.insert(std::make_pair(newId,vehicle));
}

void Player::buyPart(const PartModel& partModel)
{
	if(money < partModel.getPrice())
		throw InsufficientMoneyException();
		
	money -= partModel.getPrice();
	
	Part part(partModel);
	
	addPart(part);
}

template <class Key,class T>
std::vector<Key> getKeysFromMap(std::map<Key,T> m)
{
	std::vector<Key> keys;

	typename std::map<Key,T>::iterator i;
	
	for(i=m.begin();i!=m.end();++i)
	{
		keys.push_back(i->first);
	}
	
	return keys;
}

std::vector<int> Player::getPartIds() const
{
	return getKeysFromMap(parts);
}

std::vector<int> Player::getVehicleIds() const
{
	return getKeysFromMap(vehicles);
}

const Part& Player::getPart(int id) const
{
	if(parts.find(id) == parts.end())
		throw NoSuchPartException();
		
	return parts.find(id)->second;
}

Vehicle& Player::getVehicle(int id)
{
	if(vehicles.find(id) == vehicles.end())
		throw NoSuchVehicleException();
		
	return vehicles.find(id)->second;
}

void Player::addPart(const Part& part)
{
	int newId = 1;
	
	if(parts.rbegin() != parts.rend())
		newId = parts.rbegin()->first + 1;
		
	parts.insert(std::make_pair(newId, part));
}

void Player::removePart(int id)
{
	if(parts.find(id) == parts.end())
		throw NoSuchPartException();

	parts.erase(parts.find(id));
}

void Player::setActiveVehicleId(int id)
{
	getVehicle(id);
	
	activeVehicleId = id;
}

int Player::getActiveVehicleId()
{
	return activeVehicleId;
}

Player::Player(const std::string& name, int money):
	name(name),
	money(money),
	activeVehicleId(0)
{

}

