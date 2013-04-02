#include "clientobjectfactory.hpp"

#include <string>

#include "connection.hpp"
#include "playerproxy.hpp"

namespace Client
{

Game::Object* ObjectFactory::allocate(const Json::Value& value)
{
	std::string type = value["type"].asString();

	if(type == "Player")
		return new PlayerProxy(value, *this, connection);

	return Game::ObjectFactory::allocate(value);
}

Game::Object* ObjectFactory::deserialize(const Json::Value& serializedObject)
{
	Game::Object* object = Game::ObjectFactory::deserialize(serializedObject);

	objectIdMapper.addMapping(serializedObject["__id"].asString(), object);

	return object;
}

ObjectFactory::ObjectFactory(Connection& connection, Game::ObjectIdMapper& objectIdMapper):
	connection(connection),
	objectIdMapper(objectIdMapper)
{

}

}
