#include "vehicle.hpp"

namespace Game
{

const std::string& Vehicle::getName() const
{
	return name;
}

const std::string& Vehicle::getInfo() const
{
	return info;
}

float Vehicle::getMass() const
{
	return 0;
}

int Vehicle::getPrice() const
{
	return price;
}

int Vehicle::getYear() const
{
	return year;
}

const std::string& Vehicle::getImageName() const
{
	return imageName;
}

PartContainer::TypedSlot<Chassis>& Vehicle::getChassisSlot()
{
	return chassis;
}

const PartContainer::TypedSlot<Chassis>& Vehicle::getChassisSlot() const
{
	return chassis;
}

void Vehicle::applyPropertiesOf(const Vehicle& vehicle)
{
	name = vehicle.getName();
	price = vehicle.getPrice();
	year = vehicle.getYear();
	info = vehicle.getInfo();
	imageName = vehicle.getImageName();
}

Vehicle::Vehicle(const std::string& name, int price, int year, const std::string& info, const std::string& imageName):
	name(name),
	price(price),
	year(year),
	info(info),
	imageName(imageName)
{
	registerSlot("chassis", &chassis);
}

Vehicle::Vehicle(const Json::Value& value):
	PartContainer(value),
	chassis(value["chassis"]),
	name(value["name"].asString()),
	price(value["price"].asUInt()),
	year(value["year"].asUInt()),
	info(value["info"].asString()),
	imageName(value["imageName"].asString())
{
	registerSlot("chassis", &chassis);
}

void Vehicle::save(Json::Value& value) const
{
	PartContainer::save(value);

	value["type"] = "Vehicle";

	chassis.save(value["chassis"]);

	value["name"] = name;
	value["price"] = price;
	value["year"] = year;
	value["info"] = info;
	value["imageName"] = imageName;
}

}
