#include "machining.hpp"

#include "utils/inifile.hpp"
#include "part.hpp"

const std::string& Machining::getName() const
{
	return name;
}

int Machining::getPrice() const
{
	return price;
}

bool Machining::fitsForPart(Part& part) const
{
	if(part.getType() == type)
		return true;
	else
		return false;
}

Machining::Machining():
	name(""),
	price(0),
	type("")
{

}

Machining::Machining(const std::string& filename)
{
	load(filename);
}

void Machining::load(const std::string& filename)
{
	IniFile partFile(filename);
	
	partFile.getValue("name",name);
	partFile.getValue("price",price);
	partFile.getValue("type",type);
}
