#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include <memory>
#include <set>

#include "part.hpp"
#include "vehicle.hpp"
#include "object.hpp"
#include "container.hpp"
#include "exception.hpp"

namespace Game
{

class Player : public Object
{
	public:
		class InsufficientFundsException : public Game::Exception
		{

		};

		class NoSuchVehicleException : public Game::Exception
		{

		};

		class NoSuchPartException : public Game::Exception
		{

		};

		virtual void setName(const std::string& name);
		virtual void setActiveVehicle(Vehicle* vehicle);
		virtual void setMoney(int money);

		virtual void buyPart(const Part* part);
		virtual void buyVehicle(const Vehicle* vehicle);

		const std::string& getName() const;

		int getMoney() const;

		const Container<Vehicle>& getVehicles() const;
		const Container<Part>& getParts() const;

		Vehicle* getActiveVehicle() const;

		Player(ObjectFactory& factory);
		Player(const Json::Value& value, ObjectFactory& factory);

		virtual void save(Json::Value& value) const;

	private:
		std::string name;
		int money;
		Vehicle* activeVehicle;

		Container<Part> parts;
		Container<Vehicle> vehicles;

		ObjectFactory& factory;
};

};

#endif
