#ifndef CYLINDERHEAD_HPP
#define CYLINDERHEAD_HPP

#include <string>

#include "part.hpp"

#include "net/packet.hpp"

class CylinderHead: public Part
{
	public:
		bool load(const std::string& filename);
	
		int getCylinderCount() const;		
		int getCylinderAlignment() const;		
		int getCamshaftPosition() const;		
		
		CylinderHead(const std::string& filename);
		CylinderHead();

		friend Packet& operator<<(Packet& packet,const CylinderHead& cylinderhead);
		friend Packet& operator>>(Packet& packet,CylinderHead& cylinderhead);
		
	private:
		int m_camshaft_position;
		int m_cylinder_alignment;
		int m_cylinders;
};

#endif // CYLINDERHEAD_HPP

