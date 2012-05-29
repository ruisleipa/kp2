#include "object.hpp"

#include <algorithm>

namespace Game
{

void Object::addListener(Object::Listener* listener)
{
	listeners.push_back(listener);
}

void Object::removeListener(Object::Listener* listener)
{
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

Object& Object::operator=(const Object&)
{
	changed();
}

Object::Object(const Json::Value& value):
	Serializable(value)
{

}

void Object::changed()
{
	for(Listener* listener : listeners)
	{
		listener->onChange(this);
	}
}

};
