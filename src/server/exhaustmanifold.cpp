#include "exhaustmanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"
#include "cylinderhead.hpp"

float ExhaustManifold::getFlow() const
{
	return flow;
}

void ExhaustManifold::checkPrerequisiteParts(const Vehicle& vehicle) const
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "cylinderhead")
		{
			const CylinderHead& cylinderHead = dynamic_cast<const CylinderHead&>(part);
							
			if(cylinderHead.getCylinderCount() != cylinders)
				throw PartDoesNotFitException("EXHAUSTMANIFOLD_CYLINDERCOUNT_DOES_NOT_MATCH");
			
			if(cylinderHead.getCylinderAlignment() != cylinderAlignment)
				throw PartDoesNotFitException("EXHAUSTMANIFOLD_CYLINDERALIGNMENT_DOES_NOT_MATCH");
		}		
	}
}

void ExhaustManifold::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "exhaustmanifold")
			throw PartDoesNotFitException("NO_ROOM_FOR_EXTRA_EXHAUSTMANIFOLD");
	}
}

ExhaustManifold* ExhaustManifold::clone() const
{
	return new ExhaustManifold(*this);
}

ExhaustManifold::ExhaustManifold(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("cylinderAlignment",cylinderAlignment);
	iniFile.getValue("flow", flow);
}
