#include "cylinderblockform.hpp"

#include <string>

void CylinderBlockForm::updateOriginal()
{
	int cylinderCount = cylinderCountField->value();
	double bore = boreField->value();
	double height = heightField->value();
	
	cylinderBlock->applyPropertiesOf(Game::CylinderBlock(cylinderCount, bore, height));
}

CylinderBlockForm::CylinderBlockForm(Game::CylinderBlock* cylinderBlock, QWidget *parent):
	TypeSpecificForm(parent),
	cylinderBlock(cylinderBlock)
{
	setupUi(this);
	
	cylinderCountField->setValue(cylinderBlock->getCylinderCount());
	boreField->setValue(cylinderBlock->getBore());
	heightField->setValue(cylinderBlock->getHeight());
	
	update();
}
