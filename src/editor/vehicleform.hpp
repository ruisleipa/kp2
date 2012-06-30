#ifndef EDITOR_VEHICLEFORM_HPP
#define EDITOR_VEHICLEFORM_HPP

#include <memory>

#include "typespecificform.hpp"
#include "ui_vehicleform.h"
#include "game/vehicle.hpp"

class VehicleForm : public TypeSpecificForm, private Ui::VehicleForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();
	
		explicit VehicleForm(Game::Vehicle* vehicle, QWidget *parent = 0);

	private:
		Game::Vehicle* vehicle;
	
};

#endif
