#include "clientobjectfactory.hpp"

#include <string>

#include "connection.hpp"
#include "playerproxy.hpp"

Game::Object* ClientObjectFactory::allocate(const Json::Value& value)
{
	std::string type = value["type"].asString();
	
	if(type == "player")
		return new PlayerProxy(value, *this, connection);

	return ObjectFactory::allocate(value);
}

ClientObjectFactory::ClientObjectFactory(Connection& connection):
	connection(connection)
{

}
