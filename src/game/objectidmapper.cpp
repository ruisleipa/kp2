#include "objectidmapper.hpp"

#include <sstream>

namespace Game
{

void ObjectIdMapper::addMapping(const std::string& id, const Object* object)
{
	Game::Object* nonConst = const_cast<Game::Object*>(object);

	objectsById[id] = nonConst;
	idsByObject[nonConst] = id;

	std::cout << "added mapping " << object << " -> '" << id << "'" << std::endl;
}

const std::string& ObjectIdMapper::getId(Object* object)
{
	if(idsByObject.find(object) == idsByObject.end())
	{
		std::stringstream s;

		s << getLocalIdPrefix();
		s << nextLocalId;

		nextLocalId++;

		addMapping(s.str(), object);
	}

	return idsByObject[object];
}

const std::string& ObjectIdMapper::getId(const Object* object)
{
	Game::Object* nonConst = const_cast<Game::Object*>(object);

	if(idsByObject.find(nonConst) == idsByObject.end())
		throw NoIdError();

	return idsByObject[nonConst];
}

Object* ObjectIdMapper::getObject(const std::string& id)
{
	if(objectsById.find(id) != objectsById.end())
		return objectsById[id];

	return nullptr;
}

ObjectIdMapper::ObjectIdMapper():
	nextLocalId(0)
{

}

}
