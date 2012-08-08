#include "singleplayermenu.hpp"
#include "ui_singleplayermenu.h"

namespace Client
{

SinglePlayerMenu::SinglePlayerMenu(Connection& connection, QWidget *parent) :
	Menu(parent),
	connection(connection)
{
	setupUi(this);
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

}
