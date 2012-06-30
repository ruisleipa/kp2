#include "crankshaftform.hpp"

#include <string>

void CrankshaftForm::updateOriginal()
{
	double stroke = strokeField->value();
	
	crankshaft->applyPropertiesOf(Game::Crankshaft(stroke));
}

CrankshaftForm::CrankshaftForm(Game::Crankshaft* crankshaft, QWidget *parent):
	TypeSpecificForm(parent),
	crankshaft(crankshaft)
{
	setupUi(this);
	
	strokeField->setValue(crankshaft->getStroke());
	
	update();
}
