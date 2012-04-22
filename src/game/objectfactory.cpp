#include "objectfactory.hpp"

#include <stdexcept>

namespace Game
{

Object* ObjectFactory::create(const Json::Value& value)
{
	std::string type;

	type = value["type"].asString();

	Object* object = allocate(value);

	if(object == nullptr)
		throw std::runtime_error("Invalid object type \"" + type + "\"");

	return object;
}

}
