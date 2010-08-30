#include "cylinderhead.hpp"

#include "net/packet.hpp"
#include "inifile.hpp"

bool CylinderHead::load(const std::string& filename)
{
	if(!Part::load(filename)) return false;
	
	IniFile file;	
	if(!file.load(filename)) return false;
	
	/*
	Load camshaft position.
	*/
	std::string camshaft_position;
	
	if(!file.getValue("cam_type",camshaft_position)) return false;
	
	if(camshaft_position=="ohv")
		m_camshaft_position=CAMSHAFT_POSITION_OHV;
	else if(camshaft_position=="cih")
		m_camshaft_position=CAMSHAFT_POSITION_CIH;
	else if(camshaft_position=="ohc")
		m_camshaft_position=CAMSHAFT_POSITION_OHC;
	else
		return false;
		
	/*
	Load cylinder alignment.
	*/
	std::string cylinder_alignment;
	
	if(!file.getValue("cylinder_alignment",cylinder_alignment)) return false;
	
	if(cylinder_alignment.at(0)=='s')
	{
		m_cylinder_alignment=CYLINDER_ALIGNMENT_S;
	}
	else if(cylinder_alignment.at(0)=='v')
	{
		m_cylinder_alignment=CYLINDER_ALIGNMENT_V;
	}
	else
	{
		std::cerr << "Invalid value for \"cam_block\" in ";
		std::cerr << '"' << filename << '"' << std::endl;
		std::cerr << "Accepted values are: \"s\", \"v\"." << std::endl;
		return false;	
	}
	
	/*
	Load cylinder count.
	*/	
	if(!file.getValue("cylinders",m_cylinders)) return false;
	
	return true;
}

int CylinderHead::getCylinderCount() const
{
	return m_cylinders;
}
		
int CylinderHead::getCylinderAlignment() const
{
	return m_cylinder_alignment;
}
		
int CylinderHead::getCamshaftPosition() const
{
	return m_camshaft_position;
}

CylinderHead::CylinderHead()
{
	
}

Packet& operator<<(Packet& packet,const CylinderHead& cylinderhead)
{
	packet<<(Part&)(cylinderhead);
	
	packet<<cylinderhead.m_camshaft_position;
	packet<<cylinderhead.m_cylinder_alignment;
	packet<<cylinderhead.m_cylinders;
}

Packet& operator>>(Packet& packet,CylinderHead& cylinderhead)
{
	packet>>(Part&)(cylinderhead);

	packet>>cylinderhead.m_camshaft_position;
	packet>>cylinderhead.m_cylinder_alignment;
	packet>>cylinderhead.m_cylinders;
}
