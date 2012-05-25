#ifndef CLIENT_CARSHOPMENU_HPP
#define CLIENT_CARSHOPMENU_HPP

#include <memory>

#include "gamemenu.hpp"
#include "ui_carshopmenu.h"
#include "game/vehicle.hpp"
#include "models/vehicletablemodel.hpp"

class CarShopMenu : public GameMenu
{	
	Q_OBJECT

	public:
		explicit CarShopMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
		
	private:
		std::unique_ptr<Ui::CarShopMenu> ui;
		std::unique_ptr<VehicleTableModel> model;

		Game::Player* player;
		Game::Vehicle* vehicle;
	
	private slots:
		void onCurrentChanged(const QModelIndex&, const QModelIndex&);
		void on_cancelButton_clicked();
		void on_buyButton_clicked();
	
};

#endif
