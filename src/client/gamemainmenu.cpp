#include "gamemainmenu.hpp"

namespace Client
{

GameMainMenu::GameMainMenu(QWidget *parent) :
	GameMenu(parent),
	ui(new Ui::GameMainMenu)
{
	ui->setupUi(this);
}

void GameMainMenu::on_carShopButton_clicked()
{
	navigateTo("CarShopMenu");
}

void GameMainMenu::on_garageButton_clicked()
{
	navigateTo("GarageMenu");
}

void GameMainMenu::on_technicsButton_clicked()
{
	navigateTo("TechnicsMenu");
}

void GameMainMenu::on_loansButton_clicked()
{
	navigateTo("LoansMenu");
}

void GameMainMenu::on_sponsorsButton_clicked()
{
	navigateTo("SponsorsMenu");
}

void GameMainMenu::on_contractsButton_clicked()
{
	navigateTo("ContractsMenu");
}

void GameMainMenu::on_scoresButton_clicked()
{
	navigateTo("RankingsMenu");
}

void GameMainMenu::on_tournamentsButton_clicked()
{
	navigateTo("TournamentsMenu");
}

void GameMainMenu::on_quarterMileButton_clicked()
{
	navigateTo("QuarterMileMenu");
}

void GameMainMenu::on_longRaceButton_clicked()
{
	navigateTo("LongRaceMenu");
}

}
