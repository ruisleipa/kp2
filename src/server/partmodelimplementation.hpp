#ifndef PARTMODELIMPLEMENTATION_HPP
#define PARTMODELIMPLEMENTATION_HPP

#include <string>

class Vehicle;

class PartModelImplementation
{
	public:
		virtual const std::string& getName() const = 0;
		virtual int getPrice() const = 0;
		
		//Checks if the part can be installed in the car.
		virtual void checkInstallationConstraints(const Vehicle& vehicle) const;
		
		//Checks if the part can be kept in the car e.g. when uninstalling some
		//other part. This does not check for extra parts of this type, so the
		//part doesn't get uninstalled because it sees itself in the vehicle.
		virtual void checkKeepingConstraints(const Vehicle& vehicle) const;
		
		virtual void checkPrerequisiteParts(const Vehicle& vehicle) const;
		virtual void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;

};

#endif // PARTMODELIMPLEMENTATION_HPP

