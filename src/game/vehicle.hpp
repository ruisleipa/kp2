#ifndef GAME_VEHICLE_HPP
#define GAME_VEHICLE_HPP

#include "object.hpp"
#include "partcontainer.hpp"
#include "chassis.hpp"
#include "objectfactory.hpp"

#include <string>

namespace Game
{

class Vehicle : public PartContainer
{
	public:
		virtual const std::string& getName() const;
		virtual const std::string& getInfo() const;
		float getMass() const;
		virtual int getYear() const;
		virtual int getPrice() const;
		const std::string& getImageName() const;

		void applyPropertiesOf(const Vehicle& vehicle);

		Vehicle(const std::string& name, int price, int year, const std::string& info, const std::string& imageName);
		Vehicle(const Json::Value&, ObjectFactory&);
		virtual void save(Json::Value& value) const;

	private:
		TypedSlot<Chassis> chassis;

		std::string name;
		int price;
		int year;
		std::string info;
		std::string imageName;
};

};

#endif

