#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>

class GameState;

class InsufficientMoneyException
{

};

class NoSuchPartException
{

};

class NoSuchVehicleException
{

};

#include "part.hpp"
#include "vehicle.hpp"

class Player
{
	public:		
		const std::string& getName() const;
		void setName(const std::string& name);
		
		int getMoney() const;
		
		void buyVehicle(const std::string& modelName);
		void buyPart(const std::string& modelName);

		int getPartCount() const;
		int getVehicleCount() const;
				
		const Part& getPart(int id) const;
		const Vehicle& getVehicle(int id) const;
		
		Player(GameState& gameState,const std::string& name,int money);
		
	private:
		GameState& gameState;
		
		std::string name;
		int money;
	
		std::map<int,Vehicle> vehicles;
		std::map<int,Part> parts;
		
};

#endif // PLAYER_HPP

