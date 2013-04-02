#include "playerproxy.hpp"

#include "protocol/protocol.hpp"

namespace Client
{

void PlayerProxy::setName(const std::string& name)
{
	Player::setName(name);

	connection.createRemoteCall();

	arguments["name"] = name;

	connection.makeRemoteCall(this, "setName", arguments);
}

void PlayerProxy::setActiveVehicle(Game::Vehicle* vehicle)
{
	Player::setActiveVehicle(vehicle);

	Json::Value arguments;

	arguments["vehicle"] = connection.getId(vehicle);

	connection.makeRemoteCall(this, "setActiveVehicle", arguments);
}

void PlayerProxy::buyPart(const Game::Part* part)
{
	std::cout << "PlayerProxy::buyPart: " << part << std::endl;

	Player::buyPart(part);

	Json::Value arguments;

	arguments["part"] = connection.getId(part);

	connection.makeRemoteCall(this, "buyPart", arguments);
}

void PlayerProxy::buyVehicle(const Game::Vehicle* shopVehicle)
{
	std::cout << "PlayerProxy::buyVehicle: " << shopVehicle << std::endl;

	Player::buyVehicle(shopVehicle);

	Json::Value arguments;

	arguments["vehicleInShop"] = connection.getId(shopVehicle);

	connection.makeRemoteCall(this, "buyVehicle", arguments);
}

PlayerProxy::PlayerProxy(const Json::Value& value, Game::ObjectFactory& factory, Connection& connection):
	Player(value, factory),
	connection(connection)
{

}

}
