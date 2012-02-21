#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.hpp"

namespace Ui {
	class MainMenu;
}

class MainMenu : public Menu
{
	Q_OBJECT

public:
	explicit MainMenu(QWidget *parent = 0);
	~MainMenu();

private:
	Ui::MainMenu *ui;

private slots:
	void on_singlePlayerButton_clicked();
	void on_quitButton_clicked();
	void on_multiPlayerButton_clicked();
	void on_settingsButton_clicked();
};

#endif // MAINMENU_H
