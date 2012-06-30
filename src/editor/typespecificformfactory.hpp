#ifndef EDITOR_TYPESPECIFICFORMFACTORY_H
#define EDITOR_TYPESPECIFICFORMFACTORY_H

#include <QWidget>

#include "typespecificform.hpp"
#include "game/object.hpp"
#include "game/objectfactory.hpp"

class TypeSpecificFormFactory
{
	public:
		TypeSpecificForm* createFormFor(Game::Object* object);
		
		TypeSpecificFormFactory();

};

#endif
