#include "object.hpp"

#include <list>
#include <algorithm>
#include <stdexcept>

#include "objectfactory.hpp"

namespace Game
{

Object::Object(const Json::Value& value):
	Serializable(value)
{

}

};
