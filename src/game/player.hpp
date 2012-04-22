#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include <memory>
#include <set>

#include "part.hpp"
#include "vehicle.hpp"
#include "upgrade.hpp"
#include "object.hpp"
#include "container.hpp"

namespace Game
{

class InsufficientFundsException
{

};

class NoSuchVehicleException
{

};

class NoSuchPartException
{

};

class Player : public Object
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

		const Container<Vehicle>& getVehicles() const;
		const Container<Part>& getParts() const;

		Vehicle* getActiveVehicle() const;

		Player(ObjectFactory& factory);
		Player(const Json::Value& value, ObjectFactory& factory);

		virtual void save(Json::Value& value);

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
