#include "carshopmenu.hpp"

#include <QMessageBox>

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
	model.reset(new VehicleTableModel(state->getShopVehicles()));

	TableView* view = ui->carList;

	view->setModel(model.get());
	connect(ui->carList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex, QModelIndex)));

	view->showColumn(model->name.getIndex());
	view->showColumn(model->price.getIndex());

	view->horizontalHeader()->setResizeMode(model->name.getIndex(), QHeaderView::Stretch);

	player = state->getPlayer();
	vehicle = nullptr;
}

void CarShopMenu::onCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
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

	try
	{
		player->buyVehicle(vehicle);

		navigateToPrevious();
		navigateTo("GarageMenu");
	}
	catch(Game::Player::InsufficientFundsException)
	{
		QMessageBox msgBox;
		msgBox.setText("Rahasi eivät riitä autoon.");
		msgBox.exec();
	}

}

