#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>

#include "part.hpp"

#include "packet.hpp"

class Engine: public Part
{
	public:
		bool load(const std::string& filename);
	
		int getCylinderCount() const;		
		int getCylinderAlignment() const;		
		float getCompressionRatio() const;		
		float getVolume() const;		
		int getCamshaftPosition() const;		
		
		Engine(const std::string& filename);
		Engine();

		friend Packet& operator<<(Packet& packet,const Engine& engine);
		friend Packet& operator>>(Packet& packet,Engine& engine);
		
	private:
		int m_camshaft_position;
		int m_cylinder_alignment;
		float m_compression;
		float m_volume;
		int m_cylinders;
};

#endif // ENGINE_HPP

