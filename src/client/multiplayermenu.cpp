#include "multiplayermenu.hpp"

namespace Client
{

MultiPlayerMenu::MultiPlayerMenu(Connection& connection, QWidget *parent) :
	Menu(parent),
	connection(connection)
{
	setupUi(this);
}

void MultiPlayerMenu::on_connectButton_clicked()
{

}

void MultiPlayerMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}

}
