#include "partcontainer.hpp"

#include "part.hpp"

namespace Game
{

Part* PartContainer::Slot::getPart() const
{
	return part.get();
}

Part* PartContainer::Slot::detachPart()
{
	return part.release();
}

void PartContainer::Slot::attachPart(Part* part)
{
	if(this->part.get())
		throw AlreadyInUseException();
		
	this->part.reset(part);
}

PartContainer::Slots PartContainer::getSlots() const
{
	return registeredSlots;
}

PartContainer::Slot& PartContainer::getSlotByName(const std::string& name) const
{
	return *registeredSlots.at(name);
}

PartContainer::PartContainer(const Json::Value& value):
	Object(value)
{

}

void PartContainer::registerSlot(const std::string& name, PartContainer::Slot* slot)
{
	registeredSlots[name] = slot;
}

}
