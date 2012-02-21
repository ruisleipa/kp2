#include "exhaustpipe.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

namespace Game
{

const std::string& ExhaustPipe::getName() const
{
	return name;
}

int ExhaustPipe::getPrice() const
{
	return 0;
}

ExhaustPipe* ExhaustPipe::clone() const
{
	return new ExhaustPipe(*this);
}

ExhaustPipe::ExhaustPipe(const Json::Value& value):
	Part(value)
{
	pipeCount = value["pipeCount"].asUInt();
	diameter = value["diameter"].asDouble();

	std::stringstream ss;
	
	//For example:
	//1x3
	//3.0L S6 DOHC
	//2.6L V6 OHC
	
	ss << pipeCount;
	ss << "x";
	ss << diameter;
	ss << "\"";
	
	name = ss.str();
}

void ExhaustPipe::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "exhaustpipe";
	value["pipeCount"] = pipeCount;
	value["diameter"] = diameter;
}

}
