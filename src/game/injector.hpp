#ifndef GAME_INJECTOR_HPP
#define GAME_INJECTOR_HPP

#include "part.hpp"

namespace Game
{

class Injector: public Part
{
	public:
		Injector(const Json::Value& value);
		void save(Json::Value& value);
		
	private:
		
};

};

#endif

