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
	model.reset(new PartTableModel(state->getShopParts()));

	TableView* view = ui->shopView;

	view->setModel(model.get());
	view->showColumn(model->name.getIndex());
	view->showColumn(model->price.getIndex());

	view->horizontalHeader()->setResizeMode(model->name.getIndex(), QHeaderView::Stretch);
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
