#ifndef CLIENT_GARAGEMENU_HPP
#define CLIENT_GARAGEMENU_HPP

#include <memory>

#include "gamemenu.hpp"
#include "ui_garagemenu.h"
#include "vehicletablemodel.hpp"

class GarageMenu : public GameMenu
{	
	Q_OBJECT

	public:
		explicit GarageMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
		
	private:
		std::unique_ptr<Ui::GarageMenu> ui;
		std::unique_ptr<VehicleTableModel> model;
		
	private slots:
		void onCurrentChanged(const QModelIndex&, const QModelIndex&);
		void on_cancelButton_clicked();
};

#endif
