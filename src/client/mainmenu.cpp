#include "mainmenu.hpp"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
	Menu(parent),
	ui(new Ui::MainMenu)
{
	ui->setupUi(this);
}

MainMenu::~MainMenu()
{
	delete ui;
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
