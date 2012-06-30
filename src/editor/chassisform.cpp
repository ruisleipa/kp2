#include "chassisform.hpp"

void ChassisForm::updateOriginal()
{
	float mass = massField->value();
	float dragCoefficient = dragCoefficientField->value();
	
	Game::Chassis::Dimensions dimensions;
		
	dimensions.length = lengthField->value();
	dimensions.width = widthField->value();
	dimensions.height = heightField->value();
	dimensions.axleTrack = axleTrackField->value();
	dimensions.wheelbase = wheelbaseField->value();
	
	Game::Chassis::EngineConstraints constraints;
		
	constraints.maxVolume = maxEngineVolumeField->value();
	constraints.maxCylinderCount = maxEngineCylinderCountField->value();

	chassis->applyPropertiesOf(Game::Chassis(mass, dragCoefficient, dimensions, constraints));
}

ChassisForm::ChassisForm(Game::Chassis* chassis, QWidget *parent) :
	TypeSpecificForm(parent),
	chassis(chassis)
{
	setupUi(this);
		
	massField->setValue(chassis->getMass());
	dragCoefficientField->setValue(chassis->getDragCoefficient());
	
	Game::Chassis::Dimensions dimensions = chassis->getDimensions();
		
	lengthField->setValue(dimensions.length);
	widthField->setValue(dimensions.width);
	heightField->setValue(dimensions.height);
	axleTrackField->setValue(dimensions.axleTrack);
	wheelbaseField->setValue(dimensions.wheelbase);
	
	Game::Chassis::EngineConstraints constraints = chassis->getEngineConstraints();
	
	maxEngineVolumeField->setValue(constraints.maxVolume);
	maxEngineCylinderCountField->setValue(constraints.maxCylinderCount);
}
