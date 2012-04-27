#include "technicsmenu.hpp"

#include <QMessageBox>

TechnicsMenu::TechnicsMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::TechnicsMenu)
{
	ui->setupUi(this);
}

void TechnicsMenu::gameStateLoaded(Client::State* state)
{
	this->state = state;

	shopModel.reset(new PartTableModel(state->getShopParts()));
	TableView* shopView = ui->shopView;

	shopView->setModel(shopModel.get());
	shopView->hideAllColumns();
	shopView->showColumn(shopModel->name.getIndex());
	shopView->showColumn(shopModel->price.getIndex());
	shopView->horizontalHeader()->setResizeMode(shopModel->name.getIndex(), QHeaderView::Stretch);
	
	playerModel.reset(new PartTableModel(state->getPlayer()->getParts()));
	TableView* playerView = ui->playerView;

	playerView->setModel(playerModel.get());
	playerView->hideAllColumns();
	playerView->showColumn(playerModel->name.getIndex());
	playerView->horizontalHeader()->setResizeMode(playerModel->name.getIndex(), QHeaderView::Stretch);

	connect(state->getPlayer(), SIGNAL(changed()), this, SLOT(playerChanged()));
}

void TechnicsMenu::on_okButton_clicked()
{
	QMessageBox msgBox;
	msgBox.setText("The document has been modified.");
	msgBox.exec();
	
	navigateToPrevious();
}

void TechnicsMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}

void TechnicsMenu::playerChanged()
{
	if(state->getPlayer()->getActiveVehicle())
	{
		vehicleModel.reset(new PartTableModel(state->getPlayer()->getActiveVehicle()->getParts()));
		TableView* vehicleView = ui->vehicleView;

		vehicleView->setModel(vehicleModel.get());
		vehicleView->hideAllColumns();
		vehicleView->showColumn(vehicleModel->name.getIndex());
		vehicleView->horizontalHeader()->setResizeMode(vehicleModel->name.getIndex(), QHeaderView::Stretch);
	}
}

void TechnicsMenu::on_shopView_doubleClicked(const QModelIndex& index)
{
	Game::Part* part = shopModel->getObject(index.row());

	state->getPlayer()->buyPart(part);
}

void TechnicsMenu::on_playerView_doubleClicked(const QModelIndex& index)
{
	Game::Part* part = playerModel->getObject(index.row());

	state->getPlayer()->attachPart(part);
}

void TechnicsMenu::on_vehicleView_doubleClicked(const QModelIndex& index)
{
	Game::Part* part = vehicleModel->getObject(index.row());

	state->getPlayer()->detachPart(part);
}
