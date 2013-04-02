#include "objectfactory.hpp"

namespace Server
{

Game::Object* ObjectFactory::deserialize(const Json::Value& value)
{
	Game::Object* object = Game::ObjectFactory::deserialize(value);

	objectIdMapper.addMapping(value["__id"].asString(), object);

	return object;
}

ObjectFactory::ObjectFactory(Game::ObjectIdMapper& objectIdMapper):
	objectIdMapper(objectIdMapper)
{

}

}
