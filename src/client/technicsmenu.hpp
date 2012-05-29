#ifndef TECHNICSMENU_H
#define TECHNICSMENU_H

#include <memory>

#include "gamemenu.hpp"
#include "ui_technicsmenu.h"
#include "models/parttablemodel.hpp"

class TechnicsMenu : public GameMenu, public Game::Object::Listener
{	
	Q_OBJECT

	public:
		void onChange(Game::Object* object);

		explicit TechnicsMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
		
	private:
		std::unique_ptr<Ui::TechnicsMenu> ui;
		std::unique_ptr<PartTableModel> shopModel;
		std::unique_ptr<PartTableModel> playerModel;
		std::unique_ptr<PartTableModel> vehicleModel;
		
		Client::State* state;

	private slots:
		void on_okButton_clicked();
		void on_cancelButton_clicked();
		void playerChanged();

		void on_shopView_doubleClicked(const QModelIndex&);
		void on_playerView_doubleClicked(const QModelIndex&);
		void on_vehicleView_doubleClicked(const QModelIndex&);
};

#endif // TECHNICSMENU_H
