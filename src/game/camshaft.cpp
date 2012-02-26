#include "camshaft.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

namespace Game
{

const std::string& Camshaft::getName() const
{
	return name;
}

int Camshaft::getPrice() const
{
	return 0;
}

int Camshaft::getCylinderCount() const
{
	return cylinders;
}

const std::string& Camshaft::getCamshaftPosition() const
{
	return camshaftPosition;
}

Camshaft::Camshaft(const Json::Value& value):
	Part(value)
{
	cylinders = value["cylinderCount"].asUInt();
	camshaftPosition = value["camshaftPosition"].asString();

	std::stringstream ss;
	
	//For example:
	//V8 OHC
	//S4 CIH
	//S6 OHV
	
	ss << cylinders;
	ss << "-syl. ";	
	ss << camshaftPosition;
	ss << " nokka";
	
	name = ss.str();
}

void Camshaft::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "camshaft"; 
	value["cylinderCount"] = cylinders; 
	value["camshaftPosition"] = camshaftPosition; 
}

}
