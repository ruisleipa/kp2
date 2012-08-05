#ifndef EDITOR_CHASSISFORM_HPP
#define EDITOR_CHASSISFORM_HPP

#include "typespecificform.hpp"
#include "ui_chassisform.h"
#include "game/chassis.hpp"

namespace Editor
{

class ChassisForm : public TypeSpecificForm, private Ui::ChassisForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();

		explicit ChassisForm(Game::Chassis* chassis, QWidget *parent = 0);

	private:
		Game::Chassis* chassis;
};

};

#endif
