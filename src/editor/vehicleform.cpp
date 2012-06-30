#include "vehicleform.hpp"

void VehicleForm::updateOriginal()
{
	std::string name = nameField->text().toStdString();
	int price = 0;
	int year = yearField->value();
	std::string info = infoField->toPlainText().toStdString();
	std::string imageName;

	vehicle->applyPropertiesOf(Game::Vehicle(name, price, year, info, imageName));
}

VehicleForm::VehicleForm(Game::Vehicle* vehicle, QWidget *parent) :
	TypeSpecificForm(parent),
	vehicle(vehicle)
{
	setupUi(this);
	
	nameField->setText(vehicle->getName().c_str());
	yearField->setValue(vehicle->getYear());
	infoField->setPlainText(vehicle->getInfo().c_str());
}
