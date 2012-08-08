#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <QWidget>

#include "menu.hpp"
#include "connection.hpp"
#include "ui_singleplayermenu.h"

namespace Client
{

class SinglePlayerMenu : public Menu, private Ui::SinglePlayerMenu
{
	Q_OBJECT

	public:
		explicit SinglePlayerMenu(Connection&, QWidget *parent = 0);

	private:
		Connection& connection;

	private slots:
		void on_cancelButton_clicked();
		void on_startGameButton_clicked();
};

}

#endif
