#include "object.hpp"

#include <list>
#include <algorithm>
#include <stdexcept>

#include "objectfactory.hpp"

namespace Game
{

void Object::save(Json::Value& value)
{
	value["name"] = name;
	
	for(Object* child : children)
	{
		Json::Value v;
		child->save(v);
		value["children"].append(v);		
	}
}

Object::Object(const Json::Value& value)
{
	ObjectFactory factory;

	for(auto child : value["children"])
	{
		addChild(factory.create(child));
	}
	
	this->name = value["name"].asString();
}

Object::Object():
	parent(nullptr)
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

const std::string& Object::getName() const 
{
	return name;
}

void Object::setName(const std::string& name)
{
	this->name = name;
}

Object* Object::findChild(const std::string& name)
{
	auto pred = 
	[name](Object* o)
	{
		return (o->name == name);
	};

	auto begin = children.begin();
	auto end = children.end();

	auto i = std::find_if(begin, end, pred);

	if(i != end)
		return *i;

	for(Object* o : children)
	{
		Object* child = o->findChild(name);

		if(child)
			return child;
	}
}

Json::Value Object::getId(Object* object)
{
	Object* current = object;
	
	std::list<int> pathParts;
	
	if(!isObjectInTree(object))
		return Json::Value();
		
	while(current != this)
	{
		Object* parent = current->parent;
		
		pathParts.push_front(parent->getChildIndex(current));
		
		current = current->parent;
	}
	
	Json::Value path;
	
	for(int part : pathParts)
		path.append(part);
	
	return path;
}

Object* Object::resolveId(const Json::Value& path)
{
	std::list<int> parts;
	
	for(auto i : path)
		parts.push_back(i.asInt());
	
	Object* current = this;
	
	while(!parts.empty() && current)
	{
		current = current->getChild(parts.front());
		
		parts.pop_front();
	}

	if(!current)
		throw std::runtime_error("Cannot resolve Object path.");
	
	return current;
}

bool Object::addChild(Object* v)
{
	if(!canAddChild(v))
		return false;

	v->setParent(this);
	
	children.push_back(v);
	
	childAdded(children.size() - 1);
	
	return true;
}

void Object::removeChild(Object* v)
{
	Container::size_type i = 0;
	
	for(auto it = children.begin(); it != children.end(); ++it)
	{
		if((*it) == v)
		{	
			children.erase(it);
				
			childRemoved(i);
			
			break;
		}		
		
		i++;
	}	
}

Object* Object::clone() const
{
	return new Object(*this);
}

Object* Object::getChild(int index)
{
	return children[index];
}

#ifdef KP2_SERVER
void Object::childAdded(int index)
{

}

void Object::childRemoved(int index)
{

}

void Object::childChanged(int index)
{

}

void Object::changed()
{

}
#endif

Object::Object(const Object&)
{

}

Object& Object::operator=(const Object&)
{

}

void Object::setParent(Object* parent)
{
	if(parent)
		parent->removeChild(this);
	
	this->parent = parent;
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
