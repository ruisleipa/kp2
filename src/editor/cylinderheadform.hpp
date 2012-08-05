#ifndef EDITOR_CYLINDERHEADFORM_HPP
#define EDITOR_CYLINDERHEADFORM_HPP

#include "typespecificform.hpp"
#include "ui_cylinderheadform.h"
#include "game/cylinderhead.hpp"

namespace Editor
{

class CylinderHeadForm : public TypeSpecificForm, public Ui::CylinderHeadForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();

		explicit CylinderHeadForm(Game::CylinderHead* cylinderHead, QWidget *parent = 0);

	private:
		Game::CylinderHead* cylinderHead;

};

};

#endif
