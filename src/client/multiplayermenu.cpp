#include "multiplayermenu.hpp"

MultiPlayerMenu::MultiPlayerMenu(Connection& connection, QWidget *parent) :
	Menu(parent),
	ui(new Ui::MultiPlayerMenu),
	connection(connection)
{
	ui->setupUi(this);
}

void MultiPlayerMenu::on_connectButton_clicked()
{

}

void MultiPlayerMenu::on_cancelButton_clicked()
{
	navigateToPrevious();
}
