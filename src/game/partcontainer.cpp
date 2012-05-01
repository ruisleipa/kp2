#include "partcontainer.hpp"

namespace Game
{

void PartContainer::add(Part* part)
{
	for(Part* attachTo : *this)
	{
		int alreadyAttached = 0;

		for(Part* attachedPart : getAttachedParts(attachTo))
		{
			if(typeid(*attachedPart) == typeid(*part))
				alreadyAttached++;
		}

		if(attachTo->getAttachmentLimitOfType(part) > alreadyAttached)
		{
			attachPart(attachTo, part);
			Container::add(part);
			return;
		}
	}

	throw ExtraPartException();
}

void PartContainer::remove(Part* part)
{
	attachments.erase(part);

	for(auto& p : attachments)
	{
		p.second.remove(part);
	}

	Container::remove(part);
}

PartContainer::Parts PartContainer::getAttachedParts(Part* part) const
{
	if(attachments.find(part) != attachments.end())
		return attachments.at(part);

	return Parts();
}

PartContainer::Parts PartContainer::getAllAttachedParts(Part* part) const
{
	Parts parts = getAttachedParts(part);

	for(Part* p : parts)
	{
		Parts tmp = getAllAttachedParts(p);

		parts.insert(parts.end(), tmp.begin(), tmp.end());
	}

	return parts;
}

PartContainer::PartContainer(const Json::Value& value, ObjectFactory& factory):
	Container(value, factory)
{
	int attachToIndex = 0;

	for(auto indexesOfAttachedParts : value["attachments"])
	{
		Part* attachTo = getByIndex(attachToIndex);

		for(auto attachedPartIndex : indexesOfAttachedParts)
		{
			Part* attachedPart = getByIndex(attachedPartIndex.asInt());

			attachments[attachTo].push_back(attachedPart);
		}

		attachToIndex++;
	}
}

void PartContainer::save(Json::Value& value) const
{
	Container::save(value);

	value["attachments"].resize(0);

	for(Part* part : *this)
	{
		Json::Value attachments;

		attachments.resize(0);

		for(Part* attachedPart : getAttachedParts(part))
		{
			attachments.append(getIndexOf(attachedPart));
		}

		value["attachments"].append(attachments);
	}
}

void PartContainer::attachPart(Part* attachTo, Part* part)
{
	if(attachTo->canAttachPart(part))
		attachments[attachTo].push_back(part);
	else
		throw IncompatiblePartException();
}

}
