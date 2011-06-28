#include "engine.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Engine::getName() const
{
	return name;
}

int Engine::getPrice() const
{
	return 0;
}

const std::string& Engine::getCamshaftPosition() const
{
	return camshaftPosition;
}

const std::string& Engine::getCylinderAlignment() const
{
	return cylinderAlignment;
}
	
int Engine::getCylinderCount() const
{
	return cylinders;
}

const Curve& Engine::getTorqueCurve() const
{
	return torqueCurve;
}

int Engine::getIdleSpeed() const
{
	return 1000;
}

int Engine::getSpeedLimit() const
{
	return 8000;
}

void Engine::checkPrerequisiteParts(const Vehicle& vehicle) const
{
	if(vehicle.getModel().getMaxEngineVolume() < volume)
			throw PartDoesNotFitException("ENGINE_TOO_LARGE_FOR_CHASSIS");

	if(vehicle.getModel().getMaxEngineCylinderCount() < cylinders)
			throw PartDoesNotFitException("ENGINE_TOO_LARGE_FOR_CHASSIS");	
}

void Engine::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "engine")
			throw PartDoesNotFitException("NO_ROOM_FOR_EXTRA_ENGINE");
	}
}

Engine::Engine(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
	iniFile.getValue("cylinderAlignment",cylinderAlignment);
	
	iniFile.getValue("compression",compression);
	iniFile.getValue("volume",volume);
	
	int torqueCurvePointCount;
	
	iniFile.getValue("torqueCurvePointCount",torqueCurvePointCount);
	
	for(int i = 0; i < torqueCurvePointCount; i++)
	{
		int position;
		float value;
		
		std::stringstream ss;
		
		ss << "torqueCurve[" << i << "]";
		
		iniFile.getValue(ss.str() + ".position", position);
		iniFile.getValue(ss.str() + ".value", value);
		
		torqueCurve.addPoint(position, value);
	}
	
	iniFile.getValue("volume",volume);
		
	std::stringstream ss;
	
	//For example:
	//1.0L S4 OHV 
	//3.0L S6 DOHC
	//2.6L V6 OHC
	
	ss << volume / 1000.0;
	ss << "L ";
	
	ss << cylinderAlignment;
	ss << cylinders;
	ss << " ";
	
	ss << camshaftPosition;
	
	name = ss.str();
}
