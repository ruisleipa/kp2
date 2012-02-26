#include "object.hpp"

#include <list>
#include <algorithm>
#include <stdexcept>

#include "objectfactory.hpp"

namespace Game
{

Object* Object::clone() const
{
	return new Object(*this);
}


};
