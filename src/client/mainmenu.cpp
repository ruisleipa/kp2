#include "mainmenu.hpp"

namespace Client
{

MainMenu::MainMenu(QWidget *parent) :
	Menu(parent)
{
	setupUi(this);
}

void MainMenu::on_quitButton_clicked()
{
	QApplication::quit();
}

void MainMenu::on_multiPlayerButton_clicked()
{
	navigateTo("MultiPlayerMenu");
}

void MainMenu::on_settingsButton_clicked()
{
	navigateTo("SettingsMenu");
}

void MainMenu::on_singlePlayerButton_clicked()
{
	navigateTo("SinglePlayerMenu");
}

}
