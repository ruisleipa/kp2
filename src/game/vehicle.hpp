#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "part.hpp"
#include "container.hpp"

#include <string>

namespace Game
{

class Vehicle : public Part
{
	public:
		virtual int getPrice() const;
		const std::string& getImageName() const;

		const Container<Part>& getParts() const;

		void attachPart(Part* part);
		void detachPart(Part* part);

		virtual bool canAttachPart(const Part* part) const;

		Vehicle(const Json::Value&, ObjectFactory&);
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

		Container<Part> parts;
};

};

#endif

