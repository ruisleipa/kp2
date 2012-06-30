#ifndef EDITOR_CYLINDERBLOCKFORM_HPP
#define EDITOR_CYLINDERBLOCKFORM_HPP

#include "typespecificform.hpp"
#include "ui_cylinderblockform.h"
#include "game/cylinderblock.hpp"

class CylinderBlockForm : public TypeSpecificForm, public Ui::CylinderBlockForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();
	
		explicit CylinderBlockForm(Game::CylinderBlock* cylinderBlock, QWidget *parent = 0);

	private:
		Game::CylinderBlock* cylinderBlock;
		
};

#endif
