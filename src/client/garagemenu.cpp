#include "garagemenu.hpp"

namespace Client
{

GarageMenu::GarageMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::GarageMenu),
	vehicle(nullptr),
	state(nullptr)
{
	ui->setupUi(this);
}

void GarageMenu::gameStateLoaded(Client::State* state)
{
	this->state = state;

	model.reset(new VehicleTableModel(state->getPlayer()->getVehicles()));

	TableView* view = ui->carList;

	view->setModel(model.get());
	connect(ui->carList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex, QModelIndex)));

	view->showColumn(model->name.getIndex());
	view->showColumn(model->price.getIndex());

	view->horizontalHeader()->setResizeMode(model->name.getIndex(), QHeaderView::Stretch);
}

void GarageMenu::onCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
	vehicle = model->getObject(current.row());

	if(!vehicle)
		return;

	ui->carNameLabel->setText(vehicle->getName().c_str());
	ui->carImage->setPixmap(QPixmap(QString("gamedata/vehicleimages/") + QString(vehicle->getImageName().c_str())));
	ui->value->setText(QString::number(vehicle->getPrice()) + trUtf8(" €"));
	ui->chassisMass->setText(QString::number(vehicle->getMass()) + QString(" kg"));
	ui->engine->setText("1.0L S4 OVH\nTurbo");
	ui->fuelintake->setText("2x30mm Kaasutin");
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

