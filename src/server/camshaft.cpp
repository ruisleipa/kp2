#include "camshaft.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"
#include "cylinderhead.hpp"

const std::string& Camshaft::getName() const
{
	return name;
}

int Camshaft::getPrice() const
{
	return 0;
}

void Camshaft::checkPrerequisiteParts(const Vehicle& vehicle) const
{
	int cylinderHeadCount = 0;

	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "cylinderhead")
		{
			const CylinderHead& cylinderHead = dynamic_cast<const CylinderHead&>(part);
			
			//check if we are a right kind of a camshaft
			if(cylinderHead.getCylinderCount() != cylinders)
				throw PartDoesNotFitException("CYLINDERCOUNT_DOES_NOT_MATCH");
			
			if(cylinderHead.getCamshaftPosition() != camshaftPosition)
				throw PartDoesNotFitException("CAMSHAFT_POSITION_DOES_NOT_MATCH");
				
			cylinderHeadCount++;
		}		
	}
	
	if(cylinderHeadCount == 0)
		throw PartDoesNotFitException("NO_CYLINDERHEAD_FOR_CAMSHAFT");
}

void Camshaft::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{
	int camshaftsNeeded = 0;
	int camshaftsInstalled = 0;
	
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "cylinderhead")
		{
			const CylinderHead& cylinderHead = dynamic_cast<const CylinderHead&>(part);
							
			if(cylinderHead.isDoubleCam())
				camshaftsNeeded += 2;
			else
				camshaftsNeeded ++;
		}		
	}
	
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "camshaft")
		{
			camshaftsInstalled++;
		}
	}	
	
	if(camshaftsNeeded == camshaftsInstalled)
		throw PartDoesNotFitException("NO_ROOM_FOR_EXTRA_CAMSHAFT");
}

Camshaft* Camshaft::clone() const
{
	return new Camshaft(*this);
}

Camshaft::Camshaft(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
			
	std::stringstream ss;
	
	//For example:
	//V8 OHC
	//S4 CIH
	//S6 OHV
	
	ss << cylinders;
	ss << "-syl. ";	
	ss << camshaftPosition;
	ss << " nokka";
	
	name = ss.str();
}
