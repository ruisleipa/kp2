#include "part.hpp"

#include "upgrade.hpp"

#include <stdexcept>

namespace Game
{

const std::string& Part::getName() const
{
	return name;
}

int Part::getPrice() const
{
	return price;
}

float Part::getMass() const
{
	return mass;
}

float Part::calculateTotalMass() const
{
	float attachedMass = 0;

	for(Object* i : *this)
	{
		Part* p = dynamic_cast<Part*>(i);
	
		attachedMass += p->calculateTotalMass();
	}

	return getMass() + attachedMass;
}
	
bool Part::addPartToTree(Part* part)
{
	if(addChild(part))		
		return true;
	
	for(Object* i : *this)
		if(i->addChild(part))
			return true;			
	
	return false;
}

bool Part::canAddChild(Object* object)
{
	if(dynamic_cast<Part*>(object))
		return true;
		
	return false;
}

Part::Part(const Json::Value& value):
	Object(value)
{
	name = value["name"].asString();
	price = value["price"].asInt();
	mass = value["mass"].asDouble();
}

void Part::save(Json::Value& value)
{
	Object::save(value);

	value["name"] = name;
	value["price"] = price;
	value["mass"] = mass;
}

}
