#ifndef COOLER_HPP
#define COOLER_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Cooler: public Part
{
	public:
		int getPrice() const;
		
		Cooler(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		
};

};

#endif // COOLER_HPP

