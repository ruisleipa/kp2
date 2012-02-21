#include "singleplayermenu.hpp"
#include "ui_singleplayermenu.h"

SinglePlayerMenu::SinglePlayerMenu(Connection& connection, QWidget *parent) :
	Menu(parent),
	ui(new Ui::SinglePlayerMenu),
	connection(connection)
{
	ui->setupUi(this);
}

SinglePlayerMenu::~SinglePlayerMenu()
{
	delete ui;
}

void SinglePlayerMenu::on_startGameButton_clicked()
{
	connection.startLocalServer();
	
	navigateTo("GameLoadingScreen");
}

void SinglePlayerMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}
