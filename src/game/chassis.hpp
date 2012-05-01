#ifndef GAME_CHASSIS_HPP
#define GAME_CHASSIS_HPP

#include "part.hpp"

namespace Game
{

class Chassis : public Part
{
	public:
		virtual bool canAttachPart(const Part* part) const;
		virtual int getAttachmentLimitOfType(const Part* part) const;		
		
		Chassis(const Json::Value&);
		virtual void save(Json::Value& value) const;

	private:
		float dragCoefficient;
		float length;
		float width;
		float height;
		float wheelbase;
		int maxEngineVolume;
		int maxEngineCylinderCount;
};

};

#endif

