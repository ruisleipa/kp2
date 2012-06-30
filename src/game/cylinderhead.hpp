#ifndef GAME_CYLINDERHEAD_HPP
#define GAME_CYLINDERHEAD_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class CylinderHead: public Part
{
	public:
		int getCylinderCount() const;	
		double getBore() const;	
		double getChamberHeight() const;

		void applyPropertiesOf(const CylinderHead& cylinderHead);
				
		CylinderHead(int cylinderCount, double bore, double chamberHeight);
		CylinderHead(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		int cylinderCount;
		double bore;
		double chamberHeight;
};

};

#endif

