#ifndef GAME_CRANKSHAFT_HPP
#define GAME_CRANKSHAFT_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Crankshaft : public Part
{
	public:	
		double getStroke() const;
		
		void applyPropertiesOf(const Crankshaft& crankshaft);
	
		Crankshaft(double stroke);
		Crankshaft(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		double stroke;
};

};

#endif
