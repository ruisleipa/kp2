#ifndef PARTMODELIMPLEMENTATION_HPP
#define PARTMODELIMPLEMENTATION_HPP

#include <string>

class Vehicle;

class PartModelImplementation
{
	public:
		virtual const std::string& getName()=0;
		virtual int getPrice()=0;
		virtual bool fitsInVehicle(const Vehicle& vehicle)=0;

};

#endif // PARTMODELIMPLEMENTATION_HPP

