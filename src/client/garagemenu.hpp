#ifndef CLIENT_GARAGEMENU_HPP
#define CLIENT_GARAGEMENU_HPP

#include <memory>

#include "gamemenu.hpp"
#include "ui_garagemenu.h"
#include "models/vehicletablemodel.hpp"

namespace Client
{

class GarageMenu : public GameMenu, private Ui::GarageMenu
{
	Q_OBJECT

	public:
		explicit GarageMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);

	private:
		std::unique_ptr<VehicleTableModel> model;

		Game::Vehicle* vehicle;
		Client::State* state;

	private slots:
		void onCurrentChanged(const QModelIndex&, const QModelIndex&);
		void on_selectButton_clicked();
		void on_cancelButton_clicked();
};

}

#endif
