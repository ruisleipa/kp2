#include "cylinderheadform.hpp"

#include <string>

void CylinderHeadForm::updateOriginal()
{
	int cylinderCount = cylinderCountField->value();
	double bore = boreField->value();
	double chamberHeight = chamberHeightField->value();
	
	cylinderHead->applyPropertiesOf(Game::CylinderHead(cylinderCount, bore, chamberHeight));
}

CylinderHeadForm::CylinderHeadForm(Game::CylinderHead* cylinderHead, QWidget *parent):
	TypeSpecificForm(parent),
	cylinderHead(cylinderHead)
{
	setupUi(this);
	
	cylinderCountField->setValue(cylinderHead->getCylinderCount());
	boreField->setValue(cylinderHead->getBore());
	chamberHeightField->setValue(cylinderHead->getChamberHeight());
	
	update();
}
