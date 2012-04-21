#ifndef GAME_OBJECTFACTORY_HPP
#define GAME_OBJECTFACTORY_HPP

#include "json/value.h"
#include "object.hpp"

namespace Game
{

class ObjectFactory
{
	public:
		Object* create(const Json::Value&);

	protected:
		virtual Object* allocate(const Json::Value&) = 0;
};

};

#endif
