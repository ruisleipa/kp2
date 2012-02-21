#ifndef CLIENT_GARAGEMENU_HPP
#define CLIENT_GARAGEMENU_HPP

#include <memory>

#include "gamemenu.hpp"
#include "ui_garagemenu.h"
#include "game/vehicle.hpp"
#include "objecttablemodel.hpp"

class GarageMenu : public GameMenu
{	
	Q_OBJECT

	public:
		explicit GarageMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
		
	private:
		std::unique_ptr<Ui::GarageMenu> ui;
		std::unique_ptr<ObjectTableModel<Game::Vehicle*>> model;
		
	private slots:
		void on_carList_clicked(const QModelIndex&);
		void on_cancelButton_clicked();
};

#endif
