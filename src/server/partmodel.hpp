#ifndef PARTMODEL_HPP
#define PARTMODEL_HPP

#include <string>

#include "utils/inifile.hpp"

class PartModel;
class Vehicle;

class PartModel
{
	public:
		virtual const std::string& getName() const;	
		virtual int getPrice() const;		
		const std::string& getType() const;	
		float getWeight() const;
		
		void checkInstallationConstraints(const Vehicle& vehicle) const;
		void checkKeepingConstraints(const Vehicle& vehicle) const;
		
		virtual void checkPrerequisiteParts(const Vehicle& vehicle) const;
		virtual void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
	
		PartModel(const IniFile& partFile);
		
	private:
		void load(const std::string& filename);

		int price;
		std::string type;
		float weight;
		std::string name;
	
};

#endif // PARTMODEL_HPP

