#ifndef GAME_UPGRADE_HPP
#define GAME_UPGRADE_HPP

#include <string>

#include "object.hpp"

namespace Game
{

class Part;

class Upgrade : public Object
{
	public:
		const std::string& getName() const;	
		int getPrice() const;
		bool fitsForPart(Game::Part& part) const;
	
		Upgrade(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		std::string name;
		int price;
		std::string type;
};

};

#endif

