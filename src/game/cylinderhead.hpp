#ifndef CYLINDERHEAD_HPP
#define CYLINDERHEAD_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Camshaft;
class IntakeManifold;
class ExhaustManifold;

class CylinderHead: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;
		bool isDoubleCam() const;
		
		CylinderHead(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		std::string name;
		bool doubleCam;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinderCount;
};

};

#endif // CYLINDERHEAD_HPP

