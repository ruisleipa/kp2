#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.hpp"
#include "ui_mainmenu.h"

namespace Client
{

class MainMenu : public Menu, private Ui::MainMenu
{
	Q_OBJECT

	public:
		explicit MainMenu(QWidget *parent = 0);

	private slots:
		void on_singlePlayerButton_clicked();
		void on_quitButton_clicked();
		void on_multiPlayerButton_clicked();
		void on_settingsButton_clicked();
};

}

#endif
