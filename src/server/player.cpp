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

void Player::buyVehicle(const std::string& modelName)
{
	const VehicleModel& vehicleModel = gameState.getVehicleModel(modelName);
	
	if(money < vehicleModel.getPrice())
		throw InsufficientMoneyException();
		
	money -= vehicleModel.getPrice();
	
	Vehicle vehicle(gameState,modelName);
	
	int newId = 0;
	
	if(vehicles.rbegin() != vehicles.rend())
		newId = vehicles.rbegin()->first + 1;
	
	vehicles.insert(std::make_pair(newId,vehicle));
}

void Player::buyPart(const std::string& modelName)
{
	const PartModel& partModel = gameState.getPartModel(modelName);
		
	if(money < partModel.getPrice())
		throw InsufficientMoneyException();
		
	money -= partModel.getPrice();
	
	Part part(gameState,modelName);
	
	int newId = 0;
	
	if(parts.rbegin() != parts.rend())
		newId = parts.rbegin()->first + 1;
	
	parts.insert(std::make_pair(newId,part));
}

int Player::getPartCount() const
{
	return parts.size();
}

int Player::getVehicleCount() const
{
	return vehicles.size();
}

const Part& Player::getPart(int id) const
{
	if(parts.find(id) == parts.end())
		throw NoSuchPartException();
		
	return parts.find(id)->second;
}

const Vehicle& Player::getVehicle(int id) const
{
	if(vehicles.find(id) == vehicles.end())
		throw NoSuchVehicleException();
		
	return vehicles.find(id)->second;
}

Player::Player(GameState& gameState,const std::string& name,int money):
	gameState(gameState),
	name(name),
	money(money)
{

}

