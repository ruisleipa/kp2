#include "upgrade.hpp"

#include "utils/inifile.hpp"
#include "part.hpp"

namespace Game
{

const std::string& Upgrade::getName() const
{
	return name;
}

int Upgrade::getPrice() const
{
	return price;
}

bool Upgrade::fitsForPart(Game::Part& part) const
{
	return false;
}

Upgrade::Upgrade(const Json::Value& value):
	Object(value)
{
	name = value["name"].asString();
	price = value["price"].asUInt();
}

void Upgrade::save(Json::Value& value) const
{
	value["name"] = name;
	value["price"] = price;
}

}
