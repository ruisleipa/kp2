#include "objectfactory.hpp"

#include "json/value.h"
#include "game/objectfactory.hpp"

#include <fstream>

namespace Editor
{

Game::Object* ObjectFactory::createObject(const std::string& className)
{
	Json::Value objectTemplate;

	std::string fileName = "data/editor/templates/";
	fileName += className;

	std::ifstream(fileName) >> objectTemplate;

	Game::ObjectFactory factory;

	return factory.create(objectTemplate);
}

}
