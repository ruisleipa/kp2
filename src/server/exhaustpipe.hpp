#ifndef EXHAUSTPIPE_HPP
#define EXHAUSTPIPE_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class ExhaustPipe: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		ExhaustPipe(IniFile& iniFile);
		
	private:
		std::string name;
		
		float diameter;
		int pipeCount;		
};

#endif // EXHAUSTPIPE_HPP

