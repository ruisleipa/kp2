#ifndef EDITOR_CRANKSHAFTFORM_HPP
#define EDITOR_CRANKSHAFTFORM_HPP

#include "typespecificform.hpp"
#include "ui_crankshaftform.h"
#include "game/crankshaft.hpp"

namespace Editor
{

class CrankshaftForm : public TypeSpecificForm, public Ui::CrankshaftForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();
	
		explicit CrankshaftForm(Game::Crankshaft* crankshaft, QWidget *parent = 0);

	private:
		Game::Crankshaft* crankshaft;
		
};

};

#endif
