#include "playerproxy.hpp"

#include "protocol/protocol.hpp"

void PlayerProxy::setName(const std::string& name)
{
	std::cout << "PlayerProxy::setName: " << name << std::endl;

	Player::setName(name);

	Json::Value arguments;

	arguments["name"] = name;

	makeCall("setName", arguments);
}

void PlayerProxy::setActiveVehicle(Game::Vehicle* vehicle)
{
	std::cout << "PlayerProxy::setActiveVehicle: " << vehicle << std::endl;

	Player::setActiveVehicle(vehicle);

	Json::Value arguments;

	arguments["vehicle"] = this->getVehicles().getIndexOf(vehicle);

	makeCall("setActiveVehicle", arguments);
}

void PlayerProxy::buyPart(const Game::Part* part)
{
	std::cout << "PlayerProxy::buyPart: " << part << std::endl;

	Player::buyPart(part);

	Json::Value arguments;

	arguments["part"] = connection.getGameState().getShopParts().getIndexOf(part);

	makeCall("buyPart", arguments);
}

void PlayerProxy::buyVehicle(const Game::Vehicle* vehicle)
{
	std::cout << "PlayerProxy::buyVehicle: " << vehicle << std::endl;

	Player::buyVehicle(vehicle);

	Json::Value arguments;

	arguments["vehicle"] = connection.getGameState().getShopVehicles().getIndexOf(vehicle);

	makeCall("buyVehicle", arguments);
}

void PlayerProxy::attachPart(Game::Part* part)
{
	std::cout << "PlayerProxy::attachPart: " << part << std::endl;

	Json::Value arguments;

	arguments["part"] = this->getParts().getIndexOf(part);

	Player::attachPart(part);

	makeCall("attachPart", arguments);
}

void PlayerProxy::detachPart(Game::Part* part)
{
	std::cout << "PlayerProxy::detachPart: " << part << std::endl;

	Json::Value arguments;

	arguments["part"] = this->getActiveVehicle()->getParts().getIndexOf(part);

	Player::detachPart(part);

	makeCall("detachPart", arguments);
}

void PlayerProxy::upgradePart(Game::Part* part, const Game::Upgrade* upgrade)
{
	std::cout << "PlayerProxy::upgradePart: " << part << ", " << upgrade << std::endl;

	Player::upgradePart(part, upgrade);

	Json::Value arguments;

	arguments["part"] = this->getParts().getIndexOf(part);
	arguments["upgrade"] = connection.getGameState().getUpgrades().getIndexOf(upgrade);

	makeCall("upgradePart", arguments);
}

PlayerProxy::PlayerProxy(const Json::Value& value, Game::ObjectFactory& factory, Connection& connection):
	Player(value, factory),
	connection(connection)
{

}

void PlayerProxy::makeCall(const std::string& method, const Json::Value& arguments)
{
	Json::Value call;

	call["objectType"] = "player";
	call["objectIndex"] = getIndex();
	call["method"] = method;
	call["arguments"] = arguments;

	Net::Packet packet;
	packet.setType(Protocol::REMOTE_INVOCATION);

	Json::FastWriter fw;

	packet << fw.write(call);

	connection.writeToServer(packet);

	std::cout << call;
}

int PlayerProxy::getIndex()
{
	auto begin = connection.getGameState().getPlayers().begin();
	auto end = connection.getGameState().getPlayers().end();
	auto i = std::find(begin, end, this);

	if(i == end)
		throw InvalidPlayerException();

	return std::distance(begin, i);
}

