#include "container.hpp"

#include <list>
#include <algorithm>
#include <stdexcept>

#include "objectfactory.hpp"

namespace Game
{

Object::Object()
{

}

Object::Container::iterator Object::begin()
{
	return children.begin();
}

Object::Container::const_iterator Object::begin() const
{
	return children.begin();
}

Object::Container::iterator Object::end() 
{
	return children.end();
}

Object::Container::const_iterator Object::end() const
{
	return children.end();
}

int Object::getIndexOf(T* item) const
{
	auto it = std::find(items.begin(), items.end(), item);

	if(it == items.end())
		return -1;

	return std::distance(items.begin(), it);
}

T* Object::getByIndex(int index) const
{
	auto it = items.begin();
	
	return std::advance(it, index);

	if(it == items.end())
		return nullptr;

	return *it;
}

bool Object::add(T* item)
{
	items.push_back(item);
}

void Object::remove(T* item)
{
	auto it = std::find(items.begin(), items.end(), item);

	if(it == items.end())
		return;

	items.erase(it);
}

Object::Object(const Object&)
{

}

Object& Object::operator=(const Object&)
{

}

bool Object::canAddChild(Object*)
{
	return true;
}

bool Object::isObjectInTree(Object* object)
{
	while(object != this && object != nullptr)
		object = object->parent;
	
	if(object == this)
		return true;
	
	return false;
}

int Object::getChildIndex(Object* object)
{
	int i = 0;

	for(Object* child : children)
	{
		if(object == child)
			return i;
			
		i++;
	}
	
	return -1;
}	

};
