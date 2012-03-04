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
