#ifndef EDITOR_OBJECTFACTORY_HPP
#define EDITOR_OBJECTFACTORY_HPP

#include <string>
#include "game/object.hpp"

namespace Editor
{

class ObjectFactory
{
	public:
		Game::Object* createObject(const std::string& className);
};

};

#endif
