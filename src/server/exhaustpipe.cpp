#include "exhaustpipe.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& ExhaustPipe::getName() const
{
	return name;
}

int ExhaustPipe::getPrice() const
{
	return 0;
}

ExhaustPipe::ExhaustPipe(IniFile& iniFile)
{
	iniFile.getValue("pipeCount",pipeCount);
	iniFile.getValue("diameter",diameter);
	
	std::stringstream ss;
	
	//For example:
	//1x3
	//3.0L S6 DOHC
	//2.6L V6 OHC
	
	ss << pipeCount;
	ss << "x";
	ss << diameter;
	ss << "\"";
	
	name = ss.str();
}
