#include "tireform.hpp"

#include "json/value.h"

TireForm::TireForm(Game::Tire* original, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TireForm),
	tire(original)
{
	ui->setupUi(this);

	setWindowTitle(trUtf8("Korin tiedot"));

	Json::Value data;

	tire->save(data);

	ui->mass->setValue(data["mass"].asDouble());
	ui->dragCoefficient->setValue(data["dragCoefficient"].asDouble());
	ui->length->setValue(data["length"].asDouble());
	ui->width->setValue(data["width"].asDouble());
	ui->height->setValue(data["height"].asDouble());
	ui->axleTrack->setValue(data["axleTrack"].asDouble());
	ui->wheelbase->setValue(data["wheelbase"].asDouble());
	ui->maxEngineVolume->setValue(data["maxEngineVolume"].asInt());
	ui->maxEngineCylinderCount->setValue(data["maxEngineCylinderCount"].asInt());
}

Game::Tire TireForm::generate()
{
	Json::Value data;

	tire->save(data);

	data["mass"] = ui->mass->value();
	data["dragCoefficient"] = ui->dragCoefficient->value();
	data["length"] = ui->length->value();
	data["width"] = ui->width->value();
	data["height"] = ui->height->value();
	data["axleTrack"] = ui->axleTrack->value();
	data["wheelbase"] = ui->wheelbase->value();
	data["maxEngineVolume"] = ui->maxEngineVolume->value();
	data["maxEngineCylinderCount"] = ui->maxEngineCylinderCount->value();

	return Game::Tire(data);
}

void TireForm::on_closeButton_clicked()
{
	close();
}

void TireForm::on_saveButton_clicked()
{
	*tire = generate();
}

void TireForm::on_okButton_clicked()
{
	*tire = generate();

	close();
}
