#include "engine.hpp"

#include "packet.hpp"
#include "inifile.hpp"

bool Engine::load(const std::string& filename)
{
	if(!Part::load(filename)) return false;
	
	IniFile file;	
	if(!file.load(filename)) return false;
	
	/*
	Load camshaft position.
	*/
	std::string camshaft_position;
	
	if(!file.getValue("engine_type",camshaft_position)) return false;
	
	if(camshaft_position=="ohv")
	{
		m_camshaft_position=CAMSHAFT_POSITION_OHV;
	}
	else if(camshaft_position=="cih")
	{
		m_camshaft_position=CAMSHAFT_POSITION_CIH;
	}
	else if(camshaft_position=="ohc")
	{
		m_camshaft_position=CAMSHAFT_POSITION_OHC;
	}
	else
	{
		std::cerr<<"Invalid 'engine_type' in '"<<filename<<"'"<<std::endl;
		return false;
	}
		
	/*
	Load cylinder alignment.
	*/
	std::string cylinder_alignment;
	
	if(!file.getValue("engine_block",cylinder_alignment)) return false;
	
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
		std::cerr<<"Invalid 'engine_block' in '"<<filename<<"'"<<std::endl;
		return false;
	}
	
	/*
	Load compression ratio.
	*/	
	if(!file.getValue("compressionrate",m_compression)) return false;
	
	/*
	Load volume and convert to liters.
	*/	
	if(!file.getValue("cc",m_volume)) return false;
	m_volume /= 1000.0;
	
	/*
	Load cylinder count.
	*/	
	if(!file.getValue("cylinders",m_cylinders)) return false;
	
	/*
	Generate a new name based on data.
	TODO: Is this the final way of doing this?
	*/
	std::stringstream ss;
	ss<<m_volume<<" L ";
	
	if(m_cylinder_alignment==CYLINDER_ALIGNMENT_S)
		ss<<"S";
	else if(m_cylinder_alignment==CYLINDER_ALIGNMENT_V)
		ss<<"V";
		
	ss<<m_cylinders<<" ";
	
	if(m_camshaft_position==CAMSHAFT_POSITION_OHV)
		ss<<"OHV";
	else if(m_camshaft_position==CAMSHAFT_POSITION_CIH)
		ss<<"CIH";
	else if(m_camshaft_position==CAMSHAFT_POSITION_OHC)
		ss<<"OHC";
	
	m_name=ss.str();
	
	return true;
}

int Engine::getCylinderCount() const
{
	return m_cylinders;
}
		
int Engine::getCylinderAlignment() const
{
	return m_cylinder_alignment;
}
		
float Engine::getCompressionRatio() const
{
	return m_compression;
}
		
float Engine::getVolume() const
{
	return m_volume;
}
		
int Engine::getCamshaftPosition() const
{
	return m_camshaft_position;
}

Engine::Engine()
{
	
}

Packet& operator<<(Packet& packet,const Engine& engine)
{
	packet<<(Part&)(engine);
	
	packet<<engine.m_camshaft_position;
	packet<<engine.m_cylinder_alignment;
	packet<<engine.m_compression;
	packet<<engine.m_volume;
	packet<<engine.m_cylinders;
	
	return packet;
}

Packet& operator>>(Packet& packet,Engine& engine)
{
	packet>>(Part&)(engine);

	packet>>engine.m_camshaft_position;
	packet>>engine.m_cylinder_alignment;
	packet>>engine.m_compression;
	packet>>engine.m_volume;
	packet>>engine.m_cylinders;
	
	return packet;
}
