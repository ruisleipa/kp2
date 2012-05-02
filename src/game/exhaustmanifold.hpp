#ifndef EXHAUSTMANIFOLD_HPP
#define EXHAUSTMANIFOLD_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class IniFile;
class Vehicle;

class ExhaustManifold: public Part
{
	public:
		float getFlow() const;		
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;
		
		ExhaustManifold(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		std::string cylinderAlignment;
		int cylinderCount;
		
		float flow;		
};

};

#endif // EXHAUSTMANIFOLD_HPP

