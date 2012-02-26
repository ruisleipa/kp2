#ifndef EXHAUSTPIPE_HPP
#define EXHAUSTPIPE_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class ExhaustPipe: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		ExhaustPipe(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		std::string name;
		
		float diameter;
		int pipeCount;		
};

};

#endif // EXHAUSTPIPE_HPP

