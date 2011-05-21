#include "intakemanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"
#include "cylinderhead.hpp"

const std::string& IntakeManifold::getName() const
{
	return name;
}

int IntakeManifold::getPrice() const
{
	return 0;
}

float IntakeManifold::getFlow() const
{
	return flow;
}

void IntakeManifold::checkPrerequisiteParts(const Vehicle& vehicle) const
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "cylinderhead")
		{
			const CylinderHead& cylinderHead = part.getModel<CylinderHead>();
							
			if(cylinderHead.getCylinderCount() != cylinders)
				throw PartDoesNotFitException("INTAKEMANIFOLD_CYLINDERCOUNT_DOES_NOT_MATCH");
			
			if(cylinderHead.getCylinderAlignment() != cylinderAlignment)
				throw PartDoesNotFitException("INTAKEMANIFOLD_CYLINDERALIGNMENT_DOES_NOT_MATCH");
		}		
	}
}

void IntakeManifold::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "intakemanifold")
			throw PartDoesNotFitException("NO_ROOM_FOR_EXTRA_INTAKEMANIFOLD");
	}
}

IntakeManifold::IntakeManifold(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("cylinders", cylinders);
	iniFile.getValue("cylinderAlignment", cylinderAlignment);
	iniFile.getValue("flow", flow);
		
	std::stringstream ss;
	
	ss << cylinderAlignment;
	ss << cylinders;
	ss << " ";
	
	ss << " -imusarja ";
	ss << flow;
	
	name = ss.str();
}
