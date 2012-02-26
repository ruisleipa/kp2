#ifndef DIFFERENTIAL_HPP
#define DIFFERENTIAL_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Differential: public Part
{
	public:
		int getPrice() const;

		Differential(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		
};

};

#endif // DIFFERENTIAL_HPP

