#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "part.hpp"
#include "utils/curve.hpp"

#include <string>

namespace Game
{

class CylinderHead;

class Engine: public Part
{
	public:	
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;	
		float getVolume() const;	
		const Curve& getTorqueCurve() const;
		int getIdleSpeed() const;
		int getSpeedLimit() const;

		virtual bool canAttachPart(const Part&) const;
		
		virtual Engine* clone() const;
		
		Engine(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		bool canAttachCylinderHead(const CylinderHead&) const;

		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinderCount;
		
		float compression;
		float volume;	

		std::string name;
		
		Curve torqueCurve;
};

};

#endif // ENGINE_HPP

