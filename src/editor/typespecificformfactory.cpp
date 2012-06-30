#include "typespecificformfactory.hpp"

#include <stdexcept>

#include "crankshaftform.hpp"
#include "cylinderheadform.hpp"
#include "cylinderblockform.hpp"
#include "chassisform.hpp"
#include "vehicleform.hpp"

TypeSpecificForm* TypeSpecificFormFactory::createFormFor(Game::Object* object)
{
	TypeSpecificForm* child = nullptr;		
	
	if(Game::Crankshaft* crankshaft = dynamic_cast<Game::Crankshaft*>(object))
		child = new CrankshaftForm(crankshaft);	
	if(Game::CylinderHead* cylinderHead = dynamic_cast<Game::CylinderHead*>(object))
		child = new CylinderHeadForm(cylinderHead);	
	if(Game::CylinderBlock* cylinderBlock = dynamic_cast<Game::CylinderBlock*>(object))
		child = new CylinderBlockForm(cylinderBlock);	
	if(Game::Chassis* chassis = dynamic_cast<Game::Chassis*>(object))
		child = new ChassisForm(chassis);	
	if(Game::Vehicle* vehicle = dynamic_cast<Game::Vehicle*>(object))
		child = new VehicleForm(vehicle);		

	if(object == nullptr)
		throw std::runtime_error("No form for object type");
	
	return child;
}

TypeSpecificFormFactory::TypeSpecificFormFactory()
{

}
