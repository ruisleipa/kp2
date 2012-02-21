#ifndef CLIENT_MULTIPLAYERMENU_H
#define CLIENT_MULTIPLAYERMENU_H

#include <memory>

#include "menu.hpp"
#include "connection.hpp"
#include "ui_multiplayermenu.h"

class MultiPlayerMenu : public Menu
{
	Q_OBJECT

	public:
		explicit MultiPlayerMenu(Connection&, QWidget *parent = 0);

	private:
		std::unique_ptr<Ui::MultiPlayerMenu> ui;
		Connection& connection;

	private slots:
		void on_cancelButton_clicked();
		void on_connectButton_clicked();
};

#endif
