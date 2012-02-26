#ifndef GAME_FUELPUMP_HPP
#define GAME_FUELPUMP_HPP

#include "part.hpp"

namespace Game
{

class FuelPump: public Part
{
	public:
		FuelPump(const Json::Value& value);
		void save(Json::Value& value);
		
	private:
		
};

};

#endif

