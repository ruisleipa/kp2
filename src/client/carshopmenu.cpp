#include "carshopmenu.hpp"

CarShopMenu::CarShopMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::CarShopMenu),
	player(nullptr),
	vehicle(nullptr)
{
	ui->setupUi(this);
}

void CarShopMenu::gameStateLoaded(Client::State* state)
{
	model.reset(new ObjectTableModel<Game::Vehicle>(state->getShopVehicles()));

	TableView* view = ui->carList;

	view->setModel(model.get());
	view->setVisibleColumns({VehicleModel::NAME, VehicleModel::PRICE});

	view->horizontalHeader()->setResizeMode(VehicleModel::NAME, QHeaderView::Stretch);

	player = state->getPlayer();
	vehicle = nullptr;
}

void CarShopMenu::on_carList_clicked(const QModelIndex& current)
{
	vehicle = model->getObject(current.row());
	
	if(!vehicle)
		return;
	
	ui->carNameLabel->setText(vehicle->getName().c_str());
	ui->carImage->setPixmap(QPixmap(QString("gamedata/vehicleimages/") + QString(vehicle->getImageName().c_str())));
	ui->price->setText(QString::number(vehicle->getPrice()) + trUtf8(" e"));
	ui->chassisMass->setText(QString::number(vehicle->getMass()) + QString(" kg"));
	ui->engine->setText("1.0L S4 OVH\nTurbo");
	ui->fuelintake->setText("2x30mm Kaasutin");
}

void CarShopMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}

void CarShopMenu::on_buyButton_clicked()
{
	if(!vehicle)
		return;

	player->buyVehicle(vehicle);

	//navigateToPrevious();
	//navigateTo("GarageMenu");
}

