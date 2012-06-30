#include "editformfactory.hpp"

#include "typespecificformfactory.hpp"
#include "engineform.hpp"
#include "chassisform.hpp"
#include "vehicleform.hpp"
#include "editform.hpp"

void EditFormFactory::createEditForm(Game::Object* object)
{
	TypeSpecificFormFactory specific();

	QWidget* specificForm = specific.createForm(object);
	
	QWidget* form = new EditForm(specificForm);
	
	return form;
}
