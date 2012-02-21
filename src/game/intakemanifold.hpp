#ifndef GAME_INTAKEMANIFOLD_HPP
#define GAME_INTAKEMANIFOLD_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class IntakeManifold: public Part
{
	public:
		const std::string& getName() const;
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;
		
		virtual IntakeManifold* clone() const;
		
		IntakeManifold(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		std::string name;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinderCount;
		
		float flow;
		
};

};

#endif
