#include "garagemenu.hpp"

namespace Client
{

GarageMenu::GarageMenu(QWidget *parent) :
	GameMenu(parent),
	vehicle(nullptr),
	state(nullptr)
{
	setupUi(this);
}

void GarageMenu::gameStateLoaded(Client::State* state)
{
	this->state = state;

	model.reset(new VehicleTableModel(state->getPlayer()->getVehicles()));

	TableView* view = carList;

	view->setModel(model.get());
	connect(carList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex, QModelIndex)));

	view->showColumn(model->name.getIndex());
	view->showColumn(model->price.getIndex());

	view->horizontalHeader()->setResizeMode(model->name.getIndex(), QHeaderView::Stretch);
}

void GarageMenu::onCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
	vehicle = model->getObject(current.row());

	if(!vehicle)
		return;

	carNameLabel->setText(vehicle->getName().c_str());
	carImage->setPixmap(QPixmap(QString("gamedata/vehicleimages/") + QString(vehicle->getImageName().c_str())));
	value->setText(QString::number(vehicle->getPrice()) + trUtf8(" €"));
	chassisMass->setText(QString::number(vehicle->getMass()) + QString(" kg"));
	engine->setText("1.0L S4 OVH\nTurbo");
	fuelintake->setText("2x30mm Kaasutin");
}

void GarageMenu::on_selectButton_clicked()
{
	state->getPlayer()->setActiveVehicle(vehicle);
}

void GarageMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}

}

