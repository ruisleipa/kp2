#include "partmodelimplementation.hpp"

void PartModelImplementation::checkInstallationConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
	checkForExtraPartsOfThisType(vehicle); 
}

void PartModelImplementation::checkKeepingConstraints(const Vehicle& vehicle) const
{
	checkPrerequisiteParts(vehicle);
}

void PartModelImplementation::checkPrerequisiteParts(const Vehicle& vehicle) const
{

}

void PartModelImplementation::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{

}
