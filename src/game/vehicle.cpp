#include "vehicle.hpp"

#include "net/packet.hpp"
#include "utils/inifile.hpp"

bool Vehicle::load(const std::string& filename)
{
	IniFile file(filename);
	
	if(!file.getValue("name",m_name)) return false;
	if(!file.getValue("image",m_image_name)) return false;
	if(!file.getValue("info",m_info)) return false;
	if(!file.getValue("year",m_year)) return false;
	if(!file.getValue("weight",m_weight)) return false;
	
	std::string engine_placement;
	
	if(!file.getValue("engineplacement",engine_placement)) return false;
	
	if(engine_placement=="front")
		m_engine_placement=ENGINE_FRONT;
	else if(engine_placement=="rear")
		m_engine_placement=ENGINE_REAR;
	else
		return false;
	
	std::string drive;
		
	if(!file.getValue("drive",drive)) return false;
	
	if(drive=="front")
		m_drive=FRONT_DRIVE;
	else if(drive=="rear")
		m_drive=REAR_DRIVE;
	else
		return false;	
	
	if(!file.getValue("aerodynamics",m_drag)) return false;
	
	return true;
}

const std::string& Vehicle::getName() const
{
	return m_name;
}

const std::string& Vehicle::getImageName() const
{
	return m_image_name;
}

std::string Vehicle::getGeneralInfoString() const
{
	std::stringstream ss;
	
	ss<<m_info<<std::endl;
	ss<<std::endl;
	ss<<"• vuosimalli "<<m_year<<std::endl;
	ss<<"• korin paino "<<m_weight<<" kg"<<std::endl;
	
	ss<<"• "<<(m_drive==REAR_DRIVE?"taka":"etu")<<"vetoinen"<<std::endl;
	ss<<"• moottori "<<(m_engine_placement==ENGINE_REAR?"takana":"edessä")<<std::endl;
		
	ss<<"• ilmanvastuskerroin "<<m_drag<<std::endl;
	
	return ss.str();
}

Vehicle::Vehicle(const std::string& filename)
{
	load(filename);
}

Vehicle::Vehicle()
{

}

Packet& operator<<(Packet& packet,const Vehicle& vehicle)
{
	packet<<vehicle.m_name;
	packet<<vehicle.m_image_name;
	packet<<vehicle.m_info;
	packet<<int32_t(vehicle.m_year);
	packet<<int32_t(vehicle.m_weight);
	packet<<int32_t(vehicle.m_engine_placement);
	packet<<int32_t(vehicle.m_drive);
	packet<<vehicle.m_drag;
}

Packet& operator>>(Packet& packet,Vehicle& vehicle)
{
	packet>>vehicle.m_name;
	packet>>vehicle.m_image_name;
	packet>>vehicle.m_info;
	packet>>vehicle.m_year;
	packet>>vehicle.m_weight;
	packet>>vehicle.m_engine_placement;
	packet>>vehicle.m_drive;
	packet>>vehicle.m_drag;
}


