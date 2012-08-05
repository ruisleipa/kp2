#include "clientobjectfactory.hpp"

#include <string>

#include "connection.hpp"
#include "playerproxy.hpp"

namespace Client
{

Game::Object* ObjectFactory::allocate(const Json::Value& value)
{
	std::string type = value["type"].asString();

	if(type == "player")
		return new PlayerProxy(value, *this, connection);

	return ObjectFactory::allocate(value);
}

ObjectFactory::ObjectFactory(Connection& connection):
	connection(connection)
{

}

}
