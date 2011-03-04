#ifndef PARTMODELIMPLEMENTATION_HPP
#define PARTMODELIMPLEMENTATION_HPP

#include <string>

class Vehicle;

class PartModelImplementation
{
	public:
		virtual const std::string& getName() const = 0;
		virtual int getPrice() const = 0;
		virtual bool fitsInVehicle(const Vehicle& vehicle) const = 0;

};

#endif // PARTMODELIMPLEMENTATION_HPP

