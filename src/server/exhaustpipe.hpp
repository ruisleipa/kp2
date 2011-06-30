#ifndef EXHAUSTPIPE_HPP
#define EXHAUSTPIPE_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class ExhaustPipe: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual ExhaustPipe* clone() const;
		
		ExhaustPipe(IniFile& iniFile);
		
	private:
		std::string name;
		
		float diameter;
		int pipeCount;		
};

#endif // EXHAUSTPIPE_HPP

