#ifndef CLUTCH_HPP
#define CLUTCH_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Clutch: public Part
{
	public:
		int getPrice() const;
		
		Clutch(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		
};

};

#endif // CLUTCH_HPP

