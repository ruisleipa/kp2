#ifndef CLIENT_MULTIPLAYERMENU_H
#define CLIENT_MULTIPLAYERMENU_H

#include <memory>

#include "menu.hpp"
#include "connection.hpp"
#include "ui_multiplayermenu.h"

namespace Client
{

class MultiPlayerMenu : public Menu, private Ui::MultiPlayerMenu
{
	Q_OBJECT

	public:
		explicit MultiPlayerMenu(Connection&, QWidget *parent = 0);

	private:
		Connection& connection;

	private slots:
		void on_cancelButton_clicked();
		void on_connectButton_clicked();
};

}

#endif
