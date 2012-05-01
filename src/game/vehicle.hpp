#ifndef GAME_VEHICLE_HPP
#define GAME_VEHICLE_HPP

#include "object.hpp"
#include "part.hpp"
#include "container.hpp"

#include <string>

namespace Game
{

class Vehicle : public Object
{
	public:
		virtual const std::string& getName() const;
		float getMass() const;
		virtual int getPrice() const;
		const std::string& getImageName() const;

		const Container<Part>& getParts() const;

		void attachPart(Part* part);
		void detachPart(Part* part);

		Vehicle(const Json::Value&, ObjectFactory&);
		virtual void save(Json::Value& value) const;

	private:
		std::string name;
		int price;
		std::string info;
		std::string imageName;

		Container<Part> parts;
};

};

#endif

