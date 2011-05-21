#include "vehiclemodel.hpp"

#include "gamestate.hpp"
#include "utils/inifile.hpp"
#include "utils/string.hpp"

#include <iostream>
#include <sstream>

const std::string& VehicleModel::getName() const
{
	return name;
}

const std::string& VehicleModel::getInfo() const
{
	return info;
}

const std::string& VehicleModel::getImageName() const
{
	return imageName;
}

int VehicleModel::getChassisWeight() const
{
	return chassisWeight;
}
float VehicleModel::getDragCoefficient() const
{
	return dragCoefficient;
}

float VehicleModel::getLength() const
{
	return length;
}

float VehicleModel::getWidth() const
{
	return width;
}

float VehicleModel::getHeight() const
{
	return height;
}

float VehicleModel::getWheelbase() const
{
	return wheelbase;
}

int VehicleModel::getYear() const
{
	return year;
}

int VehicleModel::getPrice() const
{
	return price;
}

int VehicleModel::getMaxEngineVolume() const
{
	return maxEngineVolume;
}

int VehicleModel::getMaxEngineCylinderCount() const
{
	return maxEngineCylinderCount;
}

size_t VehicleModel::getPartCount() const
{
	return parts.size();
}

const Part& VehicleModel::getPart(size_t id) const
{
	if(id < parts.size())
		return parts[id];
	else
		throw NoSuchPartException();
}

VehicleModel::VehicleModel(GameState& gameState,const std::string& filename):
	gameState(gameState)
{
	load(filename);
}

void VehicleModel::load(const std::string& filename)
{
	IniFile file(filename);
	
	file.getValue("name", name);
	file.getValue("info", info);
	file.getValue("imageName", imageName);
	file.getValue("chassisWeight", chassisWeight);
	file.getValue("dragCoefficient", dragCoefficient);
	file.getValue("length", length);
	file.getValue("width", width);
	file.getValue("height", height);
	file.getValue("wheelbase", wheelbase);
	file.getValue("year", year);
	file.getValue("price", price);
	file.getValue("maxEngineVolume", maxEngineVolume);
	file.getValue("maxEngineCylinderCount", maxEngineCylinderCount);
	
	int partCount;
	
	file.getValue("partCount",partCount);
	
	for(int i = 0; i < partCount; i++)
	{
		std::stringstream ss;
		
		ss << "part";
		ss << i;
		
		std::string partPrefix = ss.str();
		
		std::string model;
		std::string machinings;
		
		file.getValue(partPrefix + ".model", model);	
		file.getValue(partPrefix + ".machinings", machinings);
		
		std::cout<<model<<" "<<machinings<<std::endl;
	
		createPart(model,machinings);
	}	
}

void VehicleModel::createPart(const std::string& modelName,const std::string& machinings)
{
	Part part(gameState.getPartModel(modelName));
	
	std::vector<std::string> machiningList = tokenize(machinings,",");
	
	std::vector<std::string>::iterator i;
	
	for(i = machiningList.begin(); i != machiningList.end(); ++i)
	{
		const Machining& machining = gameState.getMachining(*i);
	
		part.addMachining(machining);
	}
	
	parts.push_back(part);
}