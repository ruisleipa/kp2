#ifndef EXHAUSTPIPE_HPP
#define EXHAUSTPIPE_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class ExhaustPipe: public PartModelImplementation
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

