#include "technicsmenu.hpp"
#include "ui_technicsmenu.h"

#include <QMessageBox>

TechnicsMenu::TechnicsMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::TechnicsMenu)
{
	ui->setupUi(this);
}

TechnicsMenu::~TechnicsMenu()
{
	delete ui;
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
