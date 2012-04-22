#ifndef GAMEMAINMENU_H
#define GAMEMAINMENU_H

#include <memory>

#include "gamemenu.hpp"
#include "connection.hpp"
#include "ui_gamemainmenu.h"

class GameMainMenu : public GameMenu
{
	Q_OBJECT

	public:
		explicit GameMainMenu(Connection& connection, QWidget *parent = 0);

	private:
		Connection& connection;
		std::unique_ptr<Ui::GameMainMenu> ui;

	private slots:
		void on_carShopButton_clicked();
		void on_garageButton_clicked();
		void on_technicsButton_clicked();
		void on_loansButton_clicked();
		void on_sponsorsButton_clicked();
		void on_contractsButton_clicked();
		void on_scoresButton_clicked();
		void on_tournamentsButton_clicked();
		void on_quarterMileButton_clicked();
		void on_longRaceButton_clicked();

};

#endif // GAMEMAINMENU_H
