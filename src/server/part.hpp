#ifndef SERVER_PART_HPP
#define SERVER_PART_HPP

#include <string>
#include <set>

#include "utils/inifile.hpp"

class Vehicle;
class Machining;

class Part
{
	public:
		virtual const std::string& getName() const;
		virtual int getPrice() const;
		const std::string& getType() const;
		float getWeight() const;
		
		void checkInstallationConstraints(const Vehicle& vehicle) const;
		void checkKeepingConstraints(const Vehicle& vehicle) const;
		
		void addMachining(const Machining& machining);
		
		virtual Part* clone() const = 0;
		
		Part(const IniFile& partFile);
		
	protected:
		virtual void checkPrerequisiteParts(const Vehicle& vehicle) const;
		virtual void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		Part(const Part&);
		Part& operator=(const Part&);
		
	private:
		std::set<const Machining*> machinings;
		
		std::string type;
		std::string name;
		int price;
		float weight;
};

#endif

