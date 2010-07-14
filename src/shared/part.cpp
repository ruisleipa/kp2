#include "part.hpp"

#include "packet.hpp"
#include "inifile.hpp"

bool Part::load(const std::string& filename)
{
	IniFile file;	
	if(!file.load(filename)) return false;
	
	if(!file.getValue("name",m_name)) return false;
	if(!file.getValue("weight",m_weight)) return false;
	if(!file.getValue("price",m_price)) return false;
	file.getValue("info",m_info);
		
	return true;
}

const std::string& Part::getName() const
{
	return m_name;
}

const std::string& Part::getInfo() const
{
	return m_info;
}
		
float Part::getWeight() const
{
	return m_weight;
}

int Part::getPrice() const
{
	return m_price;
}

Part::Part(const std::string& filename)
{
	load(filename);
}

Part::Part()
{
	
}

Part::~Part()
{
	
}

Packet& operator<<(Packet& packet,const Part& part)
{
	packet<<part.m_name;
	packet<<part.m_info;
	packet<<part.m_weight;
	packet<<part.m_price;
}

Packet& operator>>(Packet& packet,Part& part)
{
	packet>>part.m_name;
	packet>>part.m_info;
	packet>>part.m_weight;
	packet>>part.m_price;
}
