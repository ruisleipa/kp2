#ifndef CAMSHAFT_HPP
#define CAMSHAFT_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Camshaft: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		int getCylinderCount() const;
		const std::string& getCamshaftPosition() const;
				
		virtual Camshaft* clone() const;
		
		Camshaft(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		std::string name;
		std::string camshaftPosition;
		int cylinders;
};

};

#endif // CAMSHAFT_HPP

