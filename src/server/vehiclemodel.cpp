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

int VehicleModel::getYear() const
{
	return year;
}

int VehicleModel::getPrice() const
{
	return price;
}	

int VehicleModel::getPartCount() const
{
	return parts.size();
}

const Part& VehicleModel::getPart(int id) const
{
	if(id >= 0 && id < parts.size())
		return parts[id];
	else
		throw std::runtime_error("No such part");
}

VehicleModel::VehicleModel(GameState& gameState,const std::string& filename):
	gameState(gameState)
{
	load(gameState,filename);
}

void VehicleModel::load(GameState& gameState,const std::string& filename)
{
	IniFile file(filename);
	
	file.getValue("name",name);
	file.getValue("info",info);
	file.getValue("imageName",imageName);
	file.getValue("chassisWeight",chassisWeight);
	file.getValue("year",year);
	file.getValue("price",price);

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

void VehicleModel::createPart(const std::string& model,const std::string& machinings)
{
	Part part(gameState,model);
	
	std::vector<std::string> machiningList = tokenize(machinings,",");
	
	std::vector<std::string>::iterator i;
	
	for(i = machiningList.begin(); i != machiningList.end(); ++i)
	{
		part.addMachining(*i);
	}
	
	parts.push_back(part);
}