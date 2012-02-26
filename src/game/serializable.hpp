#ifndef GAME_SERIALIZABLE_HPP
#define GAME_SERIALIZABLE_HPP

#include "json/json.h" 

namespace Game
{

class Serializable
{
	public:
		virtual void save(Json::Value&) const;
		
		Serializable() = default;
		Serializable(const Json::Value&);
};

};

#endif
