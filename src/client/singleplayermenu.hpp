#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <QWidget>

#include "menu.hpp"
#include "connection.hpp"

namespace Ui {
	class SinglePlayerMenu;
}

namespace Client
{

class SinglePlayerMenu : public Menu
{
	Q_OBJECT

public:
	explicit SinglePlayerMenu(Connection&, QWidget *parent = 0);
	~SinglePlayerMenu();

private:
	Ui::SinglePlayerMenu *ui;
	Connection& connection;

private slots:
	void on_cancelButton_clicked();
	void on_startGameButton_clicked();
};

}

#endif
