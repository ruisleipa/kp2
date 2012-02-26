#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Vehicle : public Part
{
	public:
		virtual int getPrice() const;
		const std::string& getImageName() const;

		virtual bool canAttachPart(const Part& part) const;

		Vehicle(const Json::Value&);
		virtual void save(Json::Value& value) const;

	private:
		std::string info;
		std::string imageName;
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

